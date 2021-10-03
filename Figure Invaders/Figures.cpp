#include "pch.h"
#include "Figures.h"

//Figure methods

Figure::Figure() :center(CPoint(0, 0)) {
}
Figure::Figure(CPoint p1) :center(p1) {
}
Figure:: ~Figure() {
}
CPoint Figure ::getPoint() const {
	return center;
}
void Figure:: Shift(int dx, int dy) {
	center.x += dx;
	center.y += dy;
}

//Line Methods

IMPLEMENT_SERIAL(Line, CObject, 1)

Line::Line() :length(1), horizontal(false) {
}
Line::Line(CPoint p1, int l, bool flag) :Figure(p1), length(l), horizontal(flag) {
}
Line:: ~Line() {
}
void Line::Serialize(CArchive& ar) {
	{
		CObject::Serialize(ar);
		if (ar.IsStoring())
		{
			ar << center;
			ar << length;
		}
		else
		{
			ar >> center;
			ar >> length;
		}
	}
}
void Line::Draw(CDC* dc) const {
	dc->MoveTo(center);
	dc->LineTo(this->getEnd());
}
CPoint Line::getEnd() const {
	CPoint end;
	if (horizontal)
	{
		end.x = center.x - length;
		end.y = center.y;
		return end;
	}
	else
	{
		end.x = center.x;
		end.y = center.y - length;
		return end;
	}
}
bool Line::isInside(const CPoint& P) const {
	CPoint end = this->getEnd();
	if (horizontal)
	{
		if (P.y == center.y)
		{
			if (P.x >= end.x && P.x <= center.x)
				return true;
		}
	}
	else
	{
		if (P.x == center.x)
		{
			if (P.y >= end.y && P.y <= center.y)
				return true;
		}
	}
	return false;
}

//Circle methods

IMPLEMENT_SERIAL(Circle, CObject, 1)

Circle::Circle() :radius(1) {
}
Circle::Circle(CPoint p1, int r) :Figure(p1), radius(r) {
}
Circle::~Circle() {
}
void Circle::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << center;
		ar << radius;
	}
	else
	{
		ar >> center;
		ar >> radius;
	}
}
void Circle::Draw(CDC* dc) const {
	CPoint p1, p2;
	p1.y = center.y - radius;
	p2.y = center.y + radius;
	p1.x = center.x - radius;
	p2.x = center.x + radius;
	dc->Ellipse(p1.x, p1.y, p2.x, p2.y);
}
int Circle::getRadius() const {
	return radius;
}
bool Circle::isInside(const CPoint& P) const {
	double dist;
	dist = sqrt((center.x - P.x) * (center.x - P.x) + (center.y - P.y) * (center.y - P.y));

	if (dist <= radius)
		return true;
	return false;
}

//Tringle methods

IMPLEMENT_SERIAL(Tringle, CObject, 1)

Tringle::Tringle() :Circle(){
}
Tringle::Tringle(CPoint p1, int r) : Circle(p1, r){
}
Tringle::~Tringle() {
}
void Tringle::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << center;
		ar << radius;
	}
	else
	{
		ar >> center;
		ar >> radius;
	}
}
void Tringle::Draw(CDC* dc) const {

	dc->MoveTo(CPoint(center.x, center.y - this->getRadius()));
	dc->LineTo(CPoint(center.x + this->getRadius(), center.y + this->getRadius()));

	dc->MoveTo(CPoint(center.x, center.y - this->getRadius()));
	dc->LineTo(CPoint(center.x - this->getRadius(), center.y + this->getRadius()));


	dc->MoveTo(CPoint(center.x - this->getRadius(), center.y + this->getRadius()));
	dc->LineTo(CPoint(center.x + this->getRadius(), center.y + this->getRadius()));

}
bool Tringle::isInside(const CPoint& P) const {
	float d1, d2, d3;
	bool has_neg, has_pos;
	CPoint v1(CPoint(center.x, center.y - this->getRadius())),
		v2(CPoint(center.x + this->getRadius(), center.y + this->getRadius())),
		v3(CPoint(center.x - this->getRadius(), center.y + this->getRadius()));

	d1 = sign(P, v1, v2);
	d2 = sign(P, v2, v3);
	d3 = sign(P, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}
float sign(CPoint p1, CPoint p2, CPoint p3) {
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

//Rectangle methods

IMPLEMENT_SERIAL(Rect, CObject, 1)

Rect::Rect() {
	length = 1;
	height = 1;
}
Rect::Rect(CPoint p1, float l, float h): Figure(p1){
	length = l;
	height = h;
}
Rect::~Rect() {
}
void Rect::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << center;
		ar << length;
		ar << height;
	}
	else
	{
		ar >> center;
		ar >> length;
		ar >> height;
	}
}
void Rect::Draw(CDC* dc) const {
	dc->MoveTo(CPoint(center.x - length / 2, center.y - height / 2));
	dc->LineTo(CPoint(center.x - length / 2, center.y + height / 2));

	dc->MoveTo(CPoint(center.x - length / 2, center.y - height / 2));
	dc->LineTo(CPoint(center.x + length / 2, center.y - height / 2));

	dc->MoveTo(CPoint(center.x + length / 2, center.y + height / 2));
	dc->LineTo(CPoint(center.x + length / 2, center.y - height / 2));

	dc->MoveTo(CPoint(center.x + length / 2, center.y + height / 2));
	dc->LineTo(CPoint(center.x - length / 2, center.y + height / 2));
}
bool Rect::isInside(const CPoint& P) const {
	if (P.x <= center.x + length / 2 && P.x >= center.x - length / 2)
		if (P.y <= center.y + height / 2 && P.y >= center.y - height / 2)
			return true;
	return false;
}
float Rect::getHeight() const {
	return height;
}
float Rect::getLength() const {
	return length;
}

//Square methods

IMPLEMENT_SERIAL(Square, CObject, 1)

Square::Square(){}
Square::Square(CPoint p1, int l):Rect(p1, l, l) {}
Square:: ~Square(){}
void Square:: Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << center;
		ar << length;
		ar << height;
	}
	else
	{
		ar >> center;
		ar >> length;
		ar >> height;
	}
}

//Trapezoid methods

IMPLEMENT_SERIAL(Trapezoid, CObject, 1)

Trapezoid::Trapezoid(){}
Trapezoid::Trapezoid(CPoint p1, float l, float h) :Rect(p1, l, h) {}
Trapezoid:: ~Trapezoid() {}
void Trapezoid::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << center;
		ar << length;
		ar << height;
	}
	else
	{
		ar >> center;
		ar >> length;
		ar >> height;
	}
}
void Trapezoid::Draw(CDC* dc) const {
	dc->MoveTo(CPoint(center.x - height / 2, center.y - height / 2));
	dc->LineTo(CPoint(center.x - length / 2, center.y + height / 2));

	dc->MoveTo(CPoint(center.x - height / 2, center.y - height / 2));
	dc->LineTo(CPoint(center.x + height / 2, center.y - height / 2));

	dc->MoveTo(CPoint(center.x + length / 2, center.y + height / 2));
	dc->LineTo(CPoint(center.x + height / 2, center.y - height / 2));

	dc->MoveTo(CPoint(center.x + length / 2, center.y + height / 2));
	dc->LineTo(CPoint(center.x - length / 2, center.y + height / 2));
}

//Alien methods

IMPLEMENT_SERIAL(Alien, CObject, 1)
int Alien:: amount = 18;
bool Alien::moveDown = false;
bool Alien::direction = true;

Alien::Alien(){}
Alien::Alien(CPoint p1, int l, bool dir) :Square(p1, l) {
} 
Alien:: ~Alien() {
}
void Alien::Serialize(CArchive& ar){
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << amount;
		ar << direction;
		ar << center;
		ar << length;
		ar << height;
		ar << moveDown;
	}
	else
	{
		ar >> amount;
		ar >> direction;
		ar >> center;
		ar >> length;
		ar >> height;
		ar >> moveDown;
	}
}
void Alien::setAmount(int a) {
	amount = a;
}
int Alien::getAmount() {
	return amount;
}
void Alien::MoveLR()
{
	if (center.x >= RightLimit)
	{
		direction = false;
		moveDown = true;
	}

	if (center.x <= LeftLimit)
	{
		direction = true;
		moveDown = true;
	}


	if (direction)
		center.x += speed;
	else
		center.x -= speed;
}
void Alien::MoveD() {
	center.y += 30;
}
bool Alien::isMoveDown() {
	return moveDown;
}
void Alien::setMoveDown() {
	moveDown = false;
}
int Alien::getPoints() const {
  	return pts;
}

//Spaceship methods
IMPLEMENT_SERIAL(Spaceship, CObject, 1)
bool Spaceship::alive = false;

Spaceship::Spaceship() {
}
Spaceship::Spaceship(CPoint p1, int l, int h) :Trapezoid(p1,l,h) {
}
Spaceship:: ~Spaceship(){}
void Spaceship::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << center;
		ar << length;
		ar << height;
		ar << alive;
	}
	else
	{
		ar >> center;
		ar >> length;
		ar >> height;
		ar >> alive;
	}
}
void Spaceship::Move() {
	center.x -= speed;
}
bool Spaceship::isAlive() {
	return alive;
}
void Spaceship::Kill() {
	alive = false;
}
void Spaceship::Reset() {
	center.x = 600;
}
void Spaceship::Alive() {
	alive = true;
}
int Spaceship::getPoints() const{
	return pts;
}

//Player methods

IMPLEMENT_SERIAL(Player, CObject, 1)

Player::Player() {}
Player::Player(CPoint p1, int r) : Tringle(p1, r){}
Player::~Player(){}
void Player::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << center;
		ar << radius;
		ar << pts;
	}
	else
	{
		ar >> center;
		ar >> radius;
		ar >> pts;
	}
}
void Player::moveLeft() {
	center.x -= speed;
}
void Player::moveRight() {
	center.x += speed;
}
void Player::addScore(int s) {
	pts += s;
}
int Player::getScore() const {
	return pts;
}

//Shot methods

IMPLEMENT_SERIAL(Shot, CObject, 1)

Shot::Shot() {
}
Shot::Shot(CPoint p1, int r) : Line(p1, r) {

}
Shot:: ~Shot() {

}
void Shot::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << center;
		ar << length;
	}
	else
	{
		ar >> center;
		ar >> length;
	}
}
void Shot::Move() {
	center.y -= 4;
}

//Explosion methods

IMPLEMENT_SERIAL(Explosion, CObject, 1)

Explosion::Explosion() {

}
Explosion::Explosion(CPoint p1, int r) :Circle(p1,r){

}
Explosion:: ~Explosion() {

}
void Explosion::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << center;
		ar << radius;
		ar << done;
		ar << half;
	}
	else
	{
		ar >> center;
		ar >> radius;
		ar >> done;
		ar >> half;
	}
}
void Explosion::Boom() {
	if (!half)
		radius++;
	else
		radius--;

	if (radius >= 20)
		half = true;

	if (half && radius <= 5)
		done = true;
}
bool Explosion::chkDone() const{
	return done;
}