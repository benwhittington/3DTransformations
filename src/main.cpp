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
	Shape<3> m_Shape0;
	Shape<3> m_Shape1;
	Point<3> m_N;
	Point<3> m_Basis;
	Point<2> m_ScreenOrigin;
	Domain m_Domain;
	Screen m_Screen;
	double m_RadsPerSecond;
	float m_SecondsSinceLastUpdate;
	float m_MinDelta;
	bool m_Pause;

public:
	Transform() {
		sAppName = "Transform";
	}

public:
	bool OnUserCreate() override {
		// pyramid
		m_Shape0 = Shape<3>(5)
				<< Point<3>(-1, 0, 0)
				<< Point<3>(1, 0, 0)
				<< Point<3>(0, 1, 0)
				<< Point<3>(0, 0, 1)
				<< Point<3>(0, 0, -1);
		
		// cube
		m_Shape1 = Shape<3>(8)
				<< Point<3>(0, 0, 0)
				<< Point<3>(1, 0, 0)
				<< Point<3>(1, 0, 1)
				<< Point<3>(0, 0, 1)
				<< Point<3>(0, 1, 0)
				<< Point<3>(1, 1, 0)
				<< Point<3>(1, 1, 1)
				<< Point<3>(0, 1, 1);

		m_Shape1 += Point<3>(1, 1, 1);
		std::cout << m_Shape1[0].x() << ", " << m_Shape1[0].x() << ", " << m_Shape1[0].x() << std::endl;

		m_N = Point<3>(0, 1, -1);
		m_Basis = Point<3>(1, 1, 1);
		m_Basis /= m_Basis.Norm();
		
		m_Domain = Domain(-2, 2, -2, 2);
		m_Screen = Screen(ScreenWidth(), ScreenHeight());
		m_ScreenOrigin = Point<2>(ScreenWidth() / 2, ScreenHeight() / 2);
		m_MinDelta = 0.005;
		m_SecondsSinceLastUpdate = m_MinDelta + 1;
		m_RadsPerSecond = pi / 2;
		m_Pause = false;

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
		const auto projected = trans::Project<X, Y>(shape, m_N);
		return map::MapFromDomainToScreen(projected, m_Domain, m_Screen);
	}

	void GetUserInput() {
		using K = olc::Key;
		double angle = m_RadsPerSecond * pi / 2500; 
		if (GetKey(K::W).bHeld) {
			trans::Rotate<X>(m_N, angle);
        }
		else if (GetKey(K::S).bHeld) {
			trans::Rotate<X>(m_N, -angle);
        }
		else if (GetKey(K::D).bHeld) {
			trans::Rotate<Y>(m_N, -angle);
        }
		else if (GetKey(K::A).bHeld) {
			trans::Rotate<Y>(m_N, angle);
        }
		else if (GetKey(K::Q).bHeld) {
			trans::Rotate<Z>(m_N, angle);
        }
		else if (GetKey(K::E).bHeld) {
			trans::Rotate<Z>(m_N, -angle);
        }
		else if (GetKey(K::EQUALS).bHeld) {
			m_Domain.ZoomOut();
        }
		else if (GetKey(K::MINUS).bHeld) {
			m_Domain.ZoomIn();
        }
		else if (GetKey(K::SPACE).bPressed) {
			m_SecondsSinceLastUpdate = 0;
			m_Pause = !m_Pause;
        }
	}

	bool OnUserUpdate(float secondsDelta) override {
		m_SecondsSinceLastUpdate += secondsDelta;
		if (m_Pause || m_SecondsSinceLastUpdate < m_MinDelta) {
			return true;
		}

		GetUserInput();
		
		const auto angle = m_RadsPerSecond * static_cast<float>(m_SecondsSinceLastUpdate);
		trans::Rotate<Y>(m_Shape0, angle); // rotate the object
		trans::Rotate<Z>(m_N, angle * 0.1); // rotate the reference frame more slowly

		Clear(olc::BLACK);
		DrawShapeAll(m_Shape0);
		DrawShapeAll(m_Shape1);

		m_SecondsSinceLastUpdate = 0;

		return true;
	}
};

int main() {
	Transform demo;
	if (demo.Construct(1024, 1024, 1, 1))
		demo.Start();

	return 0;
}