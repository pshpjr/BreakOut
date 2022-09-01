#pragma once
struct pt {
	double x, y;
	pt() = default;
	pt(const double x, const double y) : x(x), y(y) {}
	pt operator/(const double& b) const {
		pt ret{};
		ret.x = this->x / b;
		ret.y = this->y / b;
		return ret;
	}
	pt operator*(const double& b) const {
		pt ret{};
		ret.x = this->x * b;
		ret.y = this->y * b;
		return ret;
	}
	pt operator+(const pt& b) const {
		pt ret{};
		ret.x = this->x + b.x;
		ret.y = this->y + b.y;
		return ret;
	}
	pt& operator+= (const pt& b) {
		*this = *this + b;
		return *this;
	}
	pt& operator/= (const float& b) {
		*this = *this / b;
		return *this;
	}

public:
	double distSquare(const pt& b) const {
		return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
	}
};
