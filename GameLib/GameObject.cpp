#include <iostream>
#include "GameObject.h"

//This LOOOOOOOOOOOOOONG file stores classes in this order:
//Joint
//Track
//Train
//Cab
//RoadBlock
//Transform

//Global
int Joint_jointCount = 0;
int Track_trackCount = 0;
int Train_trainCount = 0;
int Cab_cabCount = 0;
int RoadBlock_roadBloackCount = 0;


//**************************************************************************************************
//Joint Class
//Constructors
Joint::Joint()
{
	jID = Joint_jointCount;
	ts = false;
	tsLockA = false;
	Joint_jointCount++;
}
Joint::Joint(Joint* NodeIn, Transform Transform)
{
	jID = Joint_jointCount;
	setNode0(NodeIn);
	setNode1(nullptr);
	setNode2(nullptr);
	transform = Transform;
	ts = false;
	tsLockA = false;
	Joint_jointCount++;
}
Joint::Joint(Joint* NodeOut0, Joint* NodeOut1, Transform Transform)
{
	jID = Joint_jointCount;
	setNode0(nullptr);
	setNode1(NodeOut0);
	setNode2(NodeOut1);
	transform = Transform;
	ts = false;
	tsLockA = false;
	Joint_jointCount++;
}
Joint::Joint(Joint* NodeIn, Joint* NodeOut0, Joint* NodeOut1, Transform Transform)
{
	jID = Joint_jointCount;
	setNode0(NodeIn);
	setNode1(NodeOut0);
	setNode2(NodeOut1);
	transform = Transform;
	ts = false;
	tsLockA = false;
	Joint_jointCount++;
}

//Destrutor
Joint::~Joint()
{
	setNode0(0);
	setNode1(0);
	setNode2(0);
}

//Methods
Track* Joint::Next(Track* From)
{
	if (From == ptrack1 || From == ptrack2)
	{
		if (!ts && From == ptrack1)
			return ptrack0;
		if (ts && From == ptrack2)
			return ptrack0;
	}
	else if (From == ptrack0)
		return ts ? ptrack2 : ptrack1;
	return nullptr;
}

void Joint::setjointID(int JID)
{
	jID = JID;
}
int Joint::getjointID()
{
	return jID;
}

void Joint::setNode0(Joint* Node)
{
	pnode0 = Node;
}
void Joint::setNode1(Joint* Node)
{
	pnode1 = Node;
}
void Joint::setNode2(Joint* Node)
{
	pnode2 = Node;
}
Joint* Joint::getNode0()
{
	return pnode0;
}
Joint* Joint::getNode1()
{
	return pnode1;
}
Joint* Joint::getNode2()
{
	return pnode2;
}

void Joint::setTrack0(Track* Track)
{
	ptrack0 = Track;
}

void Joint::setTrack1(Track* Track)
{
	ptrack1 = Track;
}

void Joint::setTrack2(Track* Track)
{
	ptrack2 = Track;
}

Track* Joint::getTrack0()
{
	return ptrack0;
}

Track* Joint::getTrack1()
{
	return ptrack1;
}

Track* Joint::getTrack2()
{
	return ptrack2;
}

void Joint::changeSwitch(bool TS)
{
	if(tsLockA == 0)
		ts = TS;
}
void Joint::inverseSwitch()
{
	if(tsLockA == 0)
		ts = !ts;
}
bool Joint::getTS()
{
	return ts;
}
void Joint::setTS(bool TS)
{
	if(tsLockA == 0)
		ts = TS;
}
void Joint::lockTS(int CabKey, int CabKeyN)
{
	if(tsLockA == 0)
	{
		tsLockA = CabKey + CabKeyN - 1 ;
		tsLockB = CabKey - CabKeyN + 1;
	}
}
void Joint::unlockTS(int CabKey)
{
	if(tsLockA == CabKey || tsLockB == CabKey)
	{
		tsLockA = 0;
		tsLockB = 0;
	}
}


//END of Joint Class
//**************************************************************************************************

//**************************************************************************************************
//Track Class
//Constructors
Track::Track()
{
	tID = -1;
}

Track::Track(Joint* node0, Joint* node1)
{
	tID = Track_trackCount;
	Track_trackCount++;
	setJoint0(node0);
	setJoint1(node1);
	hasRoadBlock = false;
}
//Destructors
Track::~Track()
{

}

//Methods
Joint* Track::Next(Joint* From)
{
	if (From == joint0)
		return joint1;
	if (From == joint1)
		return joint0;
	return nullptr;
}

void Track::setupTransform()
{
	float x, y, r, dx, dy, le;
	x = (joint1->transform.getX() + joint0->transform.getX()) / 2.0f;
	y = (joint1->transform.getY() + joint0->transform.getY()) / 2.0f;
	dx = joint1->transform.getX() - joint0->transform.getX();
	dy = joint1->transform.getY() - joint0->transform.getY();
	r =  atan2(dy, dx) * 180.0f / 3.1415f;
	if (r < 0.0f){ r += 360.0f; }
	/*if ((joint0->transform.getX() >= joint1->transform.getX()) && (joint0->transform.getY() > joint1->transform.getY()))
		if (r < 90.0f && r > 0){ r = 180.0f - r; }
	else
		if (r > 90.0f){ r = 180.0f - r; }*/
	le = sqrt(dx*dx + dy*dy);
	length = le;
	transform.Set(x, y, r);
}

void Track::settrackID(int TID)
{
	tID = TID;
}
int Track::gettrackID()
{
	return tID;
}

void Track::setJoint0(Joint* Node)
{
	joint0 = Node;
}
void Track::setJoint1(Joint* Node)
{
	joint1 = Node;
}
Joint* Track::getJoint0()
{
	return joint0;
}
Joint* Track::getJoint1()
{
	return joint1;
}

void Track::sethasRb(bool HasRB)
{
	hasRoadBlock = HasRB;
}

bool Track::gethasRB()
{
	return hasRoadBlock;
}

void Track::setroadBlock(RoadBlock* RoadBlock)
{
	roadBlock = RoadBlock;
}

RoadBlock* Track::getroadBlock()
{
	return roadBlock;
}

float Track::getLength()
{
	return length;
}

//END of Track Class
//**************************************************************************************************

//**************************************************************************************************
//Train Class
//Constructors
Train::Train()
{
	tID = -1;
	cabsNumber = 0;
	inversed = false;
}
Train::Train(int CabsNumber, Transform Transform)
{
	tID = Train_trainCount;
	transform = Transform;
	cabs = new Cab[CabsNumber];
	for (int i = 0; i < CabsNumber; i++)
	{
		(cabs + i)->transform = transform;
		(cabs + i)->setcabNumInTrain(CabsNumber);
	}
	cabsNumber = CabsNumber;
	Train_trainCount++;
	inversed = false;
}
//Destructors
Train::~Train()
{
	delete [] cabs;
}

//Methods
int Train::Move(float DeltaTime)
{
	int state;
	int blockState = 1;
	bool isRedLight = false;
	if(!inversed)
	{
		if (cabs->getonTrack()->gethasRB())
		{
			blockState = cabs->getonTrack()->getroadBlock()->getblockState();
			if (cabs->transform.DistanceTo(cabs->getonTrack()->getroadBlock()->transform)
				<= (cabs->getonTrack()->getroadBlock()->getradius()))
			{
				if(blockState == -1)
				{
					for (int i = 0; i < cabsNumber; i++)
					{
						(cabs + i)->setlastJoint((cabs + i)->getonTrack()->Next((cabs + i)->getlastJoint()));
					}
					Reverse();
				}
				else if(blockState == 0)
					isRedLight = true;
			}
		}
		for (int i = 0; i < cabsNumber; i++)
		{
			if(!isRedLight)
				state = (cabs + i)->Move(speed, DeltaTime);
			else
				state = -1;
			if(state!=-1)
				break;
		}
	}
	else
	{
		if ((cabs+cabsNumber-1)->getonTrack()->gethasRB())
		{
			blockState = (cabs+cabsNumber-1)->getonTrack()->getroadBlock()->getblockState();
			if ((cabs+cabsNumber-1)->transform.DistanceTo((cabs+cabsNumber-1)->getonTrack()->getroadBlock()->transform)
				<= ((cabs+cabsNumber-1)->getonTrack()->getroadBlock()->getradius()))
			{
				if(blockState == -1)
				{
					for (int i = cabsNumber - 1 ; i >= 0; i--)
					{
						(cabs + i)->setlastJoint((cabs + i)->getonTrack()->Next((cabs + i)->getlastJoint()));
					}
					Reverse();
				}
				else if(blockState == 0)
					isRedLight = true;
			}
		}
		for (int i = cabsNumber - 1; i >= 0; i--)
		{
			if(!isRedLight)
				state = (cabs + i)->Move(speed, DeltaTime);
			else
				state = -1;
			if(state!=-1)
				break;
		}
	}
	return state;

	
}

void Train::Reverse()
{
	inversed = !inversed;
}

void Train::settrainID(int TID)
{
	tID = TID;
}
int Train::gettrainID()
{
	return tID;
}

void Train::setdestination(int Destination)
{
	destination = Destination;
}

int Train::getdestination()
{
	return destination;
}

Cab * Train::getcabs()
{
	return cabs;
}

int Train::getcabsNumber()
{
	return cabsNumber;
}

void Train::setSpeed(float Speed)
{
	speed = Speed;
}

float Train::getSpeed()
{
	return speed;
}

//END of Train Class
//**************************************************************************************************

//**************************************************************************************************
//Cab Class
//Constructors
Cab::Cab()
{
	cID = Cab_cabCount;
	Cab_cabCount++;
	cabLength = 1.0f;
}
Cab::~Cab()
{
}
//Destructors

//Methods
int Cab::Move(float Speed, float DeltaTime)
{
	bool inRangeX, inRangeY;
	float dx, dy, d0, d1;
	inRangeX = (
		transform.getX() <= onTrack->getJoint0()->transform.getX() &&
		transform.getX() >= onTrack->getJoint1()->transform.getX()
		) || (
		transform.getX() <= onTrack->getJoint1()->transform.getX() &&
		transform.getX() >= onTrack->getJoint0()->transform.getX()
		);
	inRangeY = (
		transform.getY() <= onTrack->getJoint0()->transform.getY() &&
		transform.getY() >= onTrack->getJoint1()->transform.getY()
		) || (
		transform.getY() <= onTrack->getJoint1()->transform.getY() &&
		transform.getY() >= onTrack->getJoint0()->transform.getY()
		);
	if (inRangeX && inRangeY)
	{
		dx = Speed * DeltaTime * cos(transform.getR() / 180.0f * 3.1415f);
		dy = Speed * DeltaTime * sin(transform.getR() / 180.0f * 3.1415f);
		//std::cout << "Dx: " << dx << "Dy: " << dy << "OnTrack: " << onTrack->gettrackID() << std::endl;
		if (lastJoint == onTrack->getJoint0())
			transform.Move(dx, dy);
		else
			transform.Move(-dx, -dy);
	}
	else
	{
		d0 = transform.DistanceTo(onTrack->getJoint0()->transform);
		d1 = transform.DistanceTo(onTrack->getJoint1()->transform);
		if (d0 < d1)
		{
			lastJoint = onTrack->getJoint0();
			transform.MoveTo(onTrack->getJoint0()->transform);
			lastJoint->lockTS(cID, cabNumInTrain);
			lastJoint->unlockTS(cID);
			onTrack = onTrack->getJoint0()->Next(onTrack);
			if(onTrack!=nullptr)
				transform.Rotate(onTrack->transform);
			else
				return lastJoint->getjointID();
		}
		else
		{
			lastJoint = onTrack->getJoint1();
			transform.MoveTo(onTrack->getJoint1()->transform);
			lastJoint->lockTS(cID, cabNumInTrain);
			lastJoint->unlockTS(cID);
			onTrack = onTrack->getJoint1()->Next(onTrack);
			if(onTrack!=nullptr)
				transform.Rotate(onTrack->transform);
			else
				return lastJoint->getjointID();
		}
	}
	return -1;

}

void Cab::settrainID(int TID)
{
	tID = TID;
}

int Cab::gettrainID()
{
	return tID;
}
void Cab::setcabID(int CID)
{
	cID = CID;
}
int Cab::getcabID()
{
	return cID;
}
void Cab::setonTrack(Track* Track)
{
	onTrack = Track;
}
Track* Cab::getonTrack()
{
	return onTrack;
}
void Cab::setlastJoint(Joint* Joint)
{
	lastJoint = Joint;
}
Joint* Cab::getlastJoint()
{
	return lastJoint;
}

void Cab::setcabLength(float CabLength)
{
	cabLength = CabLength;
}
float Cab::getcabLength()
{
	return cabLength;
}

void Cab::setcabNumInTrain(int CabNum)
{
	cabNumInTrain = CabNum;
}
int Cab::getcabNumInTrain()
{
	return cabNumInTrain;
}

//END of Cab Class
//**************************************************************************************************

//**************************************************************************************************
//RoadBlock Class
//Constructors
RoadBlock::RoadBlock()
{
	rbID = RoadBlock_roadBloackCount;
	RoadBlock_roadBloackCount++;
	onTrack = nullptr;
	location = 0.5f;
	radius = 0.0f;
	blockState = -1;
}
RoadBlock::RoadBlock(Track* OnTrack, float Location, float Radius)
{
	rbID = RoadBlock_roadBloackCount;
	onTrack = OnTrack;
	onTrack->sethasRb(true);
	location = Location;
	radius = Radius;
	blockState = -1;
	SetupTransform();
	RoadBlock_roadBloackCount++;
}
//Destructors
RoadBlock::~RoadBlock()
{

}

//Methods
void RoadBlock::SetupTransform()
{
	if (location > 1.0f){ location = 1.0f; }
	if (location < 0.0f){ location = 0.0f; }
	transform.SetXY(location * onTrack->getJoint0()->transform.getX() + (1 - location)*onTrack->getJoint1()->transform.getX(),
		location * onTrack->getJoint0()->transform.getY() + (1 - location) * onTrack->getJoint1()->transform.getY());
}

void RoadBlock::setroadBlockID(int RBID)
{
	rbID = RBID;
}
int RoadBlock::getroadBlockID()
{
	return rbID;
}

void RoadBlock::setonTrack(Track* OnTrack)
{
	onTrack = OnTrack;
}
Track* RoadBlock::getonTrack()
{
	return onTrack;
}

void RoadBlock::setlocation(float Location)
{
	location = Location;
}
float RoadBlock::getlocation()
{
	return location;
}

void RoadBlock::setradius(float Radius)
{
	radius = Radius;
}
float RoadBlock::getradius()
{
	return radius;
}

void RoadBlock::setblockState(int BlockState)
{
	blockState = BlockState;
}
int RoadBlock::getblockState()
{
	return blockState;
}

//END of RoadBlcok Class
//**************************************************************************************************

//**************************************************************************************************
//Transform Class
Transform::Transform(float X, float Y, float Rotation)
{
	x = X;
	y = Y;
	rotation = Rotation;
}
Transform::~Transform()
{

}

//methods
float Transform::DistanceTo(Transform target)
{
	float dx, dy, d;
	dx = target.getX() - x;
	dy = target.getY() - y;
	d = sqrt(dx*dx + dy*dy);
	return d;
}
float Transform::DistanceTo(float X, float Y)
{
	float dx, dy, d;
	dx = X - x;
	dy = Y - y;
	d = sqrt(dx*dx + dy*dy);
	return d;
}
float Transform::AngleBetween(Transform target)
{
	float targetRotation = target.getR();
	float angle = targetRotation - rotation;
	if (angle < 0){ angle = -angle; }
	while (rotation >= 360.0f){ rotation -= 360.0f; }
	while (rotation < 0.0f){ rotation += 360.0f; }
	return angle;
}
void Transform::Move(Transform DeltaVector)
{
	x += DeltaVector.getX();
	y += DeltaVector.getY();
}
void Transform::MoveTo(Transform target)
{
	x = target.getX();
	y = target.getY();
}
void Transform::Move(float Dx, float Dy)
{
	x += Dx;
	y += Dy;
}
void Transform::MoveTo(float X, float Y)
{
	x = X;
	y = Y;
}
void Transform::Rotate(Transform target)
{
	rotation = target.getR();
}
void Transform::Rotate(float Dr)
{
	rotation += Dr;
	while (rotation >= 360.0f){ rotation -= 360.0f; }
	while (rotation < 0.0f){ rotation += 360.0f; }
}
void Transform::Scale(float Factor)
{
	x*=Factor;
	y*=Factor;
}
Transform Transform::Normalize()
{
	Transform normal;
	float nx, ny, nr, mag;
	nx = x;
	ny = y;
	nr = rotation;
	mag = sqrt(x * x + y * y);
	if(mag != 0)
	{
		nx = nx/mag;
		ny = ny/mag;
	}
	else
	{
		nx = 0.0f;
		ny = 0.0f;
	}
	normal.Set(nx,ny,nr);
	SetXY(nx,ny);
	return normal;
}

Transform Transform::Intersection(Transform t1, Transform t2, Transform t3, Transform t4)
{
	float x, y, x1, y1, x2, y2, a1, b1, a2, b2;
	float m, n;
	x1 = t1.getX();
	y1 = t1.getY();
	x2 = t2.getX();
	y2 = t2.getY();
	a1 = t3.getX();
	b1 = t3.getY();
	a2 = t4.getX();
	b2 = t4.getY();

	m = (x1 - x2)/(y1 - y2);
	n = (a1 - a2)/(b1 - b2);
	y = (y1 * m - b1 * n + a1 - x1)/(m - n);
	x = x1 + (m/(m-n))*(y1 * n - b1 * n + a1 - x1);
	Transform t = Transform(x, y ,0.0f);
	return t;
}

//Properties
void Transform::Set(float X, float Y, float Rotation)
{
	x = X;
	y = Y;
	rotation = Rotation;
}
void Transform::SetXY(float X, float Y)
{
	x = X;
	y = Y;
}
void Transform::SetR(float Rotation)
{
	rotation = Rotation;
}

float Transform::getX(){ return x; }
float Transform::getY(){ return y; }
float Transform::getR(){ return rotation; }
//END of Transform Class
//**************************************************************************************************
