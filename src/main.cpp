#define OLC_PGE_APPLICATION
#include <olcPixelGameEngine.h>
#include <vector>
#include <iostream>

#include "domain.hpp"
#include "mapRange.hpp"
#include "point.hpp"
#include "shape.hpp"
#include "transform.hpp"

static constexpr double pi = 3.141592;

class Transform : public olc::PixelGameEngine {
	Shape<3> m_shape0;
	Shape<3> m_shape1;
	Point<3> m_n;
	Point<3> m_basis;
	Point<2> m_screenOrigin;
	Domain m_domain;
	Screen m_screen;
	double m_radsPerSecond;
	float m_secondsSinceLastUpdate;
	float m_minDelta;
	bool m_pause;

public:
	Transform() {
		sAppName = "Transform";
	}

public:
	bool OnUserCreate() override {
		// pyramid
		m_shape0 = Shape<3>(5)
				<< Point<3>(-1, 0, 0)
				<< Point<3>(1, 0, 0)
				<< Point<3>(0, 1, 0)
				<< Point<3>(0, 0, 1)
				<< Point<3>(0, 0, -1);
		
		// cube
		m_shape1 = Shape<3>(8)
				<< Point<3>(0, 0, 0)
				<< Point<3>(1, 0, 0)
				<< Point<3>(1, 0, 1)
				<< Point<3>(0, 0, 1)
				<< Point<3>(0, 1, 0)
				<< Point<3>(1, 1, 0)
				<< Point<3>(1, 1, 1)
				<< Point<3>(0, 1, 1);

		m_shape1 += Point<3>(1, 1, 1);
		std::cout << m_shape1[0].x() << ", " << m_shape1[0].x() << ", " << m_shape1[0].x() << std::endl;

		m_n = Point<3>(0, 1, -1);
		// m_n /= m_n.
		m_basis = Point<3>(1, 1, 1);
		m_basis /= m_basis.Norm();
		m_domain = Domain(-2, 2, -2, 2);
		m_screen = Screen(ScreenWidth(), ScreenHeight());
		m_screenOrigin = Point<2>(ScreenWidth() / 2, ScreenHeight() / 2);
		m_minDelta = 0.005;
		m_secondsSinceLastUpdate = m_minDelta + 1;
		m_radsPerSecond = pi / 2;
		m_pause = false;

		return true;
	}

	void DrawShapeConsecutive(const Shape<3>& shapeIn) {
		// iterates throught the points drawing lines from the current point to the next
		const auto shapeDraw = ProjectAndMap(shapeIn);
		for (size_t i = 0; i < shapeDraw.NumPoints(); ++i) {
			const auto next = (i + 1) % shapeDraw.NumPoints();
			DrawLine(shapeDraw[i].x(), shapeDraw[i].y(), shapeDraw[next].x(), shapeDraw[next].y());
		}
	}

	void DrawShapeAll(Shape<3>& shapeIn) {
		// draws line from each point to every other point
		const auto shapeDraw = ProjectAndMap(shapeIn);
		for (size_t i = 0; i < shapeDraw.NumPoints(); ++i) {
			for (size_t j = i; j < shapeDraw.NumPoints(); ++j) {
				DrawLine(shapeDraw[i].x(), shapeDraw[i].y(), shapeDraw[j].x(), shapeDraw[j].y());
			}
		}
	}

	Shape<2> ProjectAndMap(const Shape<3>& shape) {
		const auto projected = trans::Project<X, Y>(shape, m_n);
		return map::MapFromDomainToScreen(projected, m_domain, m_screen);
	}

	void GetUserInput() {
		using K = olc::Key;
		double angle = m_radsPerSecond * pi / 2500; 
		if (GetKey(K::W).bHeld) {
			trans::Rotate<X>(m_n, angle);
        }
		else if (GetKey(K::S).bHeld) {
			trans::Rotate<X>(m_n, -angle);
        }
		else if (GetKey(K::D).bHeld) {
			trans::Rotate<Y>(m_n, -angle);
        }
		else if (GetKey(K::A).bHeld) {
			trans::Rotate<Y>(m_n, angle);
        }
		else if (GetKey(K::Q).bHeld) {
			trans::Rotate<Z>(m_n, angle);
        }
		else if (GetKey(K::E).bHeld) {
			trans::Rotate<Z>(m_n, -angle);
        }
		else if (GetKey(K::EQUALS).bHeld) {
			m_domain.ZoomOut();
        }
		else if (GetKey(K::MINUS).bHeld) {
			m_domain.ZoomIn();
        }
		else if (GetKey(K::SPACE).bPressed) {
			m_secondsSinceLastUpdate = 0;
			m_pause = !m_pause;
        }
	}

	bool OnUserUpdate(float secondsDelta) override {
		m_secondsSinceLastUpdate += secondsDelta;
		if (m_pause || m_secondsSinceLastUpdate < m_minDelta) {
			return true;
		}

		GetUserInput();
		// const auto angle = m_radsPerSecond * static_cast<float>(m_secondsSinceLastUpdate);
		std::cout << m_n[0] << ", " << m_n[1] << ", " << m_n[2] << std::endl;
		// trans::Rotate<Y>(m_shape0, angle); // rotate the object
		// trans::Rotate<Z>(m_n, angle * 0.1); // rotate the reference frame more slowly

		Clear(olc::BLACK);
		DrawShapeAll(m_shape0);
		DrawShapeAll(m_shape1);

		m_secondsSinceLastUpdate = 0;
		return true;
	}
};

int main() {
	Transform demo;
	if (demo.Construct(1024, 1024, 1, 1))
		demo.Start();

	return 0;
}