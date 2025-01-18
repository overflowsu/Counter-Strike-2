#pragma once
#include <Windows.h>
#include <numbers>
#include <cmath>

extern int screenWidth;
extern int screenHeight;
struct view_matrix_t {
	float* operator[ ](int index){ return matrix[index]; }
	float matrix[4][4];
};
struct Vector3 {
	constexpr Vector3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept : x(x), y(y), z(z) { }
	constexpr const Vector3& operator-(const Vector3& other) const noexcept { return Vector3{ x - other.x, y - other.y, z - other.z }; }
	constexpr const Vector3& operator+(const Vector3& other) const noexcept { return Vector3{ x + other.x, y + other.y, z + other.z }; }
	constexpr const Vector3& operator/(const float factor) const noexcept { return Vector3{ x / factor, y / factor, z / factor }; }
	constexpr const Vector3& operator*(const float factor) const noexcept { return Vector3{ x * factor, y * factor, z * factor }; }
	Vector3 w2s(view_matrix_t matrix) const {
		Vector3 screen;
		float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];
		if (w < 0.01f) return { -1, -1, -1 };
		screen.x = (matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3]) / w;
		screen.y = (matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3]) / w;
		screen.z = 0.0f;
		screen.x = (screen.x + 1.0f) * (screenWidth / 2.0f);
		screen.y = (1.0f - screen.y) * (screenHeight / 2.0f);
		return screen;
	}
	float x, y, z;
};