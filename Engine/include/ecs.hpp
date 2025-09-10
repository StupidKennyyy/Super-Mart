#pragma once
#include <components.hpp>
#include <cstdint>
#include <bitset>
#include <queue>
#include <cassert>
#include <array>
#include <unordered_map>
#include <memory>
#include <set>
#include <string>

using Entity = std::uint32_t;

const Entity MAX_ENTITES = 5000;

constexpr Entity NULLENTITY = MAX_ENTITES;

using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;



class EntityManager {

public:

	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITES; entity++)
		{
			m_AvailableEntites.push(entity);
		}
	}

	Entity CreateEntity()
	{
		assert(m_LivingEntityCount < MAX_ENTITES && "Too many entites in existance.");
		
		// Take an ID from the front of the queue
		Entity id = m_AvailableEntites.front();
		m_AvailableEntites.pop();
		m_LivingEntityCount++;

		return id;
	}

	void DestoryEntity(Entity entity)
	{
		assert(entity < MAX_ENTITES && "Entity out of range.");

		// Invalidate the destroyed entity's signature
		m_Signatures[entity].reset();

		// Put the destroyed ID at the back of the queue
		m_AvailableEntites.push(entity);
		--m_LivingEntityCount;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITES && "Entity out of range.");

		// Put this entity's signature into the array
		m_Signatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITES && "Entity out of range.");

		// Get this entity's signature from the array
		return m_Signatures[entity];
	}

private:

	std::queue<Entity> m_AvailableEntites{};

	std::array<Signature, MAX_ENTITES> m_Signatures{};

	uint32_t m_LivingEntityCount{};

};



class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};



template<typename T>
class ComponentArray : public IComponentArray {

public:

	void InsertData(Entity entity, T component)
	{
		assert(m_EntityToIndexMap.find(entity) == m_EntityToIndexMap.end() && "Component added to same entity more than once.");

		// Put the new entry at the and and update the maps
		size_t newIndex = m_Size;
		m_EntityToIndexMap[entity] = newIndex;
		m_IndexToEntityMap[newIndex] = entity;
		m_ComponentArray[newIndex] = component;
		m_Size++;
	}

	void RemoveData(Entity entity)
	{
		assert(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = m_EntityToIndexMap[entity];
		size_t indexOfLastElement = m_Size - 1;
		m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
		m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		m_EntityToIndexMap.erase(entity);
		m_IndexToEntityMap.erase(indexOfLastElement);

		--m_Size;
	}

	T& GetData(Entity entity)
	{
		assert(m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end() && "Retrueving non-existent component.");

		// Return a reference to the entity's component
		return m_ComponentArray[m_EntityToIndexMap[entity]];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (m_EntityToIndexMap.find(entity) != m_EntityToIndexMap.end())
			RemoveData(entity);
	}

private:

	std::array<T, MAX_ENTITES> m_ComponentArray;
	
	// Map from entity ID to an array index
	std::unordered_map<Entity, size_t> m_EntityToIndexMap;

	// Map from an array index to an entity ID
	std::unordered_map<size_t, Entity> m_IndexToEntityMap;

	// Total size of valid entries in the array
	size_t m_Size;
};



class ComponentManager {

public:

	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) == m_ComponentTypes.end() && "Registering component type more than once.");
		
		// Add this component type to the component type map
		m_ComponentTypes.insert({ typeName, m_NextComponentType });
		
		// Create a ComponentArray pointer and add it to the component arrays map
		m_ComponentsArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
		
		// Increment the value so that the next component registered will be different
		m_NextComponentType++;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");

		// Return rhis component's type - used for creating signatures
		return m_ComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		// Add component to the array for an entity
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		// Get a reference to a component from the array for an entity
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : m_ComponentsArrays)
		{
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:

	// Map from type string pointer to a component type
	std::unordered_map<const char*, ComponentType> m_ComponentTypes{};

	// Map from type string pointer to component array
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_ComponentsArrays{};

	// The component type to be assigned to the next registered component - starting at 0
	ComponentType m_NextComponentType{};

	// Convenience function to get the statucally casted pointer to the ComponentArray of type T
	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(m_ComponentsArrays[typeName]);
	}

};



class System {

public:
	std::set<Entity> m_Entites;

};


class SystemManager {

public:

	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const std::string typeName = typeid(T).name();

		assert(M_Systems.find(typeName) == M_Systems.end() && "Registering system more than once.");

		// Create a pointer to the system and return it so it can be used externally
		auto system = std::make_shared<T>();
		M_Systems.insert(std::make_pair(typeName,std::static_pointer_cast<System>(system)));
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		const std::string typeName = typeid(T).name();

		assert(M_Systems.find(typeName) != M_Systems.end() && "System used before registered");

		// Set the signature for this system
		m_Signatures.insert(std::make_pair(typeName, signature));
	}

	void EntityDestroyed(Entity entity)
	{
		// Erase destroyed entity from all system lists
		
		for (auto const& pair : M_Systems)
		{
			auto const& system = pair.second;
			system->m_Entites.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : M_Systems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = m_Signatures[type];

			// Entity signature matches system signature - insert into set
			if ((entitySignature & systemSignature) == systemSignature)
				system->m_Entites.insert(entity);

			// Entity signature does not match system signature - erase from set
			else
				system->m_Entites.erase(entity);
		}
	}

private:

	// Map from system type string pointer to a signature
	std::unordered_map<std::string, Signature> m_Signatures{};

	// Map from system type string pointer to a system pointer
	std::unordered_map<std::string, std::shared_ptr<System>> M_Systems{};

};



class Coordinator {

public:

	void Init()
	{
		m_ComponentManager = std::make_unique<ComponentManager>();
		m_EntityManager = std::make_unique<EntityManager>();
		m_SystemManager = std::make_unique<SystemManager>();
	}
	
	// Entity methods

	Entity CreateEntity()
	{
		return m_EntityManager->CreateEntity();
	}

	void DestroyEntity(Entity entity)
	{
		m_EntityManager->DestoryEntity(entity);
		m_ComponentManager->EntityDestroyed(entity);
		m_SystemManager->EntityDestroyed(entity);
	}

	// Component methods

	template<typename T>
	void RegisterComponent()
	{
		m_ComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		m_ComponentManager->AddComponent<T>(entity, component);

		auto signature = m_EntityManager->GetSignature(entity);
		signature.set(m_ComponentManager->GetComponentType<T>(), true);
		m_EntityManager->SetSignature(entity, signature);

		m_SystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		m_ComponentManager->RemoveComponent<T>(entity);

		auto signature = m_EntityManager->GetSignature(entity);
		signature.set(m_ComponentManager->GetComponentType<T>(), false);
		m_EntityManager->SetSignature(entity, signature);

		m_SystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return m_ComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return m_ComponentManager->GetComponentType<T>();
	}

	// System methods

	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return m_SystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		m_SystemManager->SetSignature<T>(signature);
	}

private:

	std::unique_ptr<ComponentManager> m_ComponentManager;
	std::unique_ptr<EntityManager> m_EntityManager;
	std::unique_ptr<SystemManager> m_SystemManager;

};
 
