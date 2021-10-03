#pragma once
#include "pch.h"

class Figure : public CObject {

protected:
	CPoint center;
	
public:
	Figure();
	Figure(CPoint p1);
	virtual ~Figure();
	virtual void Serialize(CArchive& ar) = 0;
	virtual void Draw(CDC* dc) const = 0;
	CPoint getPoint() const;
	virtual bool isInside(const CPoint& P) const = 0;
	virtual void Shift(int dx, int dy);
};

class Line : public Figure {

	DECLARE_SERIAL(Line)

protected:
	int length;
	bool horizontal;

public:
	Line();
	Line(CPoint p1, int l, bool flag = false);
	virtual ~Line();
	void Serialize(CArchive& ar);
	virtual void Draw(CDC* dc) const;
	CPoint getEnd() const;
	virtual bool isInside(const CPoint& P) const;
};

class Circle : public Figure {

	DECLARE_SERIAL(Circle)

protected:
	int radius;

public:
	Circle();
	Circle(CPoint p1, int r);
	virtual ~Circle();
	void Serialize(CArchive& ar);
	virtual void Draw(CDC* dc) const;
	int getRadius() const;
	virtual bool isInside(const CPoint& P) const;
};

class Tringle : public Circle {

	DECLARE_SERIAL(Tringle)

public: 
	Tringle();
	Tringle(CPoint p1, int r);
	virtual ~Tringle();
	void Serialize(CArchive& ar);
	virtual void Draw(CDC* dc) const;
	virtual bool isInside(const CPoint& P) const;
	friend float sign(CPoint p1, CPoint p2, CPoint p3);

};

class Rect : public Figure {

	DECLARE_SERIAL(Rect)

protected:
	float length;
	float height;

public:
	Rect();
	Rect(CPoint p1, float l, float h);
	virtual ~Rect();
	void Serialize(CArchive& ar);
	virtual void Draw(CDC* dc) const;
	virtual bool isInside(const CPoint& P) const;
	float getHeight() const;
	float getLength() const;
};

class Square : public Rect {
	DECLARE_SERIAL(Square)
public:
	Square();
	Square(CPoint p1, int l);
	virtual ~Square();
	void Serialize(CArchive& ar);
};

class Trapezoid : public Rect{
	DECLARE_SERIAL(Trapezoid)
public:
	Trapezoid();
	Trapezoid(CPoint p1, float l, float h);
	virtual ~Trapezoid();
	void Serialize(CArchive& ar);
	virtual void Draw(CDC* dc) const;
};

class Alien :public Square {
	DECLARE_SERIAL(Alien)
protected:
	static bool moveDown;
	static bool direction;
	const int pts = 100;
	const float speed = 1;
	static int amount;
	const int LeftLimit = 20;
	const int RightLimit = 535;
public:
	Alien();
	Alien(CPoint p1, int l, bool down = 0);
	virtual ~Alien();
	void Serialize(CArchive& ar);
	void MoveLR();
	void MoveD();
	static bool isMoveDown();
	static void setMoveDown();
	static void setAmount(int a);
	static int getAmount();
	int getPoints() const;

};

class Spaceship : public Trapezoid {
	DECLARE_SERIAL(Spaceship)
protected:
	static bool alive;
	const int pts = 500;
	const float speed = 2;
public:
	Spaceship();
	Spaceship(CPoint p1, int l, int h);
	virtual ~Spaceship();
	void Serialize(CArchive& ar);
	void Move();
	static bool isAlive();
	static void Kill();
	void Reset();
	static void Alive();
	int getPoints() const;
};

class Player : public Tringle {
	DECLARE_SERIAL(Player)
protected:
	const int speed = 8;
	int pts = 0;
public:
	Player();
	Player(CPoint p1, int r);
	virtual ~Player();
	void Serialize(CArchive& ar);
	void moveLeft();
	void moveRight();
	void addScore(int s);
	int getScore() const;
};

class Explosion : public Circle {
	DECLARE_SERIAL(Explosion)
protected:
	bool half = false;
	bool done = false;
public:
	Explosion();
	Explosion(CPoint p1, int r);
	virtual ~Explosion();
	void Serialize(CArchive& ar);
	void Boom();
	bool chkDone() const;
};

class Shot : public Line {
	DECLARE_SERIAL(Shot)
protected:
	const int speed = 4;
public:
	Shot();
	Shot(CPoint p1, int r);
	virtual ~Shot();
	void Serialize(CArchive& ar);
	void Move();
};

