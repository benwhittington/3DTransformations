#define OLC_PGE_APPLICATION
#include <olcPixelGameEngine.h>
#include <vector>
#include <iostream>

#include "shape.hpp"
#include "mapRange.hpp"
#include "domain.hpp"
#include "transform.hpp"

static constexpr double pi = 3.141592;

class Transform : public olc::PixelGameEngine {
	Shape<3> m_shape;
	Point<3> m_n;
	Point<2> m_screenOrigin;
	Domain m_domain;
	Screen m_screen;
	double m_radsPerSecond;
	float m_timeSinceLastUpdate;
	float m_minDelta;
	bool m_pause;

public:
	Transform() {
		sAppName = "Transform";
	}

public:
	bool OnUserCreate() override {
		m_shape = Shape<3>(5)
				<< Point<3>(-1, 0, 0)
				<< Point<3>(1, 0, 0)
				<< Point<3>(0, 1, 0)
				<< Point<3>(0, 0, 1)
				<< Point<3>(0, 0, -1);

		m_n = Point<3>(0, 1, -1);
		m_domain = Domain(-2, 2, -2, 2);
		m_screen = Screen(ScreenWidth(), ScreenHeight());
		m_screenOrigin = Point<2>(ScreenWidth() / 2, ScreenHeight() / 2);
		m_minDelta = 0.005;
		m_timeSinceLastUpdate = m_minDelta + 1;
		m_radsPerSecond = pi / 2;
		m_pause = false;

		return true;
	}

	void DrawShapeConsecutive(Shape<2>& shape) {
		// iterates throught the points drawing lines from the current point to the next
		for (size_t i = 0; i < shape.NumPoints(); ++i) {
			const auto next = (i + 1) % shape.NumPoints();
			DrawLine(shape[i].x(), shape[i].y(), shape[next].x(), shape[next].y());
		}
	}

	void DrawShapeAll(Shape<2>& shape) {
		// draws line from each point to every other point
		for (size_t i = 0; i < shape.NumPoints(); ++i) {
			for (size_t j = i; j < shape.NumPoints(); ++j) {
				DrawLine(shape[i].x(), shape[i].y(), shape[j].x(), shape[j].y());
			}
		}
	}

	bool OnUserUpdate(float secondsDelta) override {
		m_timeSinceLastUpdate += secondsDelta;

		if (GetKey(olc::Key::SPACE).bPressed) {
			m_pause = !m_pause;
        }

		if (m_pause || m_timeSinceLastUpdate < m_minDelta) {
			return true;
		}

		const double angle = m_radsPerSecond * static_cast<float>(m_timeSinceLastUpdate);

		trans::Rotate<Y>(m_shape, angle); // rotate the object
		trans::Rotate<Z>(m_n, angle * 0.1); // rotate the reference frame
		
		auto projected = trans::Project<X, Y>(m_shape, m_n);
		auto mapped = trans::MapFromDomainToScreen(projected, m_domain, m_screen);

		Clear(olc::BLACK);
		DrawShapeAll(mapped);

		m_timeSinceLastUpdate = 0;
		return true;
	}
};

int main() {
	Transform demo;
	if (demo.Construct(1024, 1024, 1, 1))
		demo.Start();

	return 0;
}