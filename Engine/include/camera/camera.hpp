#pragma once

#include <vector>
#include <cstdint>
#include <queue>
#include <cassert>
#include <array>
#include <SDL3/SDL.h>
#include <components/components.hpp>


using Camera = uint8_t;

constexpr Camera MAX_CAMERA_COUNT = 10;

constexpr Camera INVALID_CAMERA = MAX_CAMERA_COUNT;



struct CameraData {

	Vector2 Position;

};

class CameraManager {

private:

	std::queue<Camera> m_AvailableCameras;

	std::array<CameraData, MAX_CAMERA_COUNT> m_CameraDatas;

	Camera m_CameraCount = 0;

	Camera m_ActiveCamera = INVALID_CAMERA;

public:

	CameraManager()
	{
		for (Camera camera = 0; camera < MAX_CAMERA_COUNT; camera++)
			m_AvailableCameras.push(camera);
	}

	Camera CreateCamera()
	{
		assert(m_CameraCount < MAX_CAMERA_COUNT && "Too many cameras in existance.");

		Camera id = m_AvailableCameras.front();
		m_AvailableCameras.pop();

		m_CameraCount++;
		return id;
	}

	void DestroyCamera(Camera camera)
	{
		assert(camera < MAX_CAMERA_COUNT && "Camera out of range.");

		m_CameraDatas[camera] = CameraData{};
		m_AvailableCameras.push(camera);
		m_CameraCount--;
	}

	CameraData& GetData(Camera camera)
	{
		assert(camera < MAX_CAMERA_COUNT && "Camera out of range.");

		return m_CameraDatas[camera];

	}

	void SetData(Camera camera, const CameraData data)
	{
		assert(camera < MAX_CAMERA_COUNT && "Camera out of range.");

		m_CameraDatas[camera] = data;

	}

	Camera GetActiveCount() const
	{
		return m_CameraCount;
	}

	Camera GetActiveCamera() const
	{
		return m_ActiveCamera;
	}

	void SetActiveCamera(Camera camera)
	{
		if (camera < MAX_CAMERA_COUNT)
			m_ActiveCamera = camera;
		else
			m_ActiveCamera = INVALID_CAMERA;
	}

	CameraData& GetActiveCameraData()
	{
		if (m_ActiveCamera == INVALID_CAMERA)
			return m_CameraDatas[0];
		else
			return m_CameraDatas[m_ActiveCamera];
	}

};

