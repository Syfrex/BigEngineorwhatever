#pragma once
namespace Big
{
	class Color
	{
	public:
		Color();
		Color(const Color& copeColor);
		Color(float red, float green, float blue, float alpha = 1.0f);
		~Color();

		float operator [](int index);

		//RGBA - Red Green Blue Aplha Values 0.0 - 1.0
		float color[4];

		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Black;
		static const Color Transparent;
		static const Color Blue;
		static const Color Magenta;
		static const Color Yellow;
	};
}

