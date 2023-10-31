#ifndef DPOINT
#define DPOINT

struct Point
{
	int x, y;
	inline Point operator+(Point operand)
	{
		return { x + operand.x, y + operand.y };
	}
	inline Point operator-(Point operand)
	{
		return { x - operand.x, y - operand.y };
	}
	bool operator==(Point operand)
	{
		return (x == operand.x && y == operand.y);
	}
	bool operator!=(Point operand)
	{
		return !(x == operand.x && y == operand.y);
	}
};

constexpr Point PointLeft() { return { 0,-1 }; }
constexpr Point PointUp() { return { -1,0 }; }
constexpr Point PointRight() { return { 0,1 }; }
constexpr Point PointDown() { return { 1,0 }; }


#endif