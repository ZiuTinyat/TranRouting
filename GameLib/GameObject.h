class Joint;
class Track;
class Train;
class Cab;
class RoadBlock;
class Transform;

class Transform
{
	/*
		A Transform class is the basic element for every game object. This class will 
	store the position and rotation of the object. The position properties can be used 
	in GUI programming: x and y can be directly used as coordinate in GDI drawing. Also,
	some convenient functions are provided to simplify the calculation code.
	*/
public:
	//Constructors
	Transform(float X = 0.0f, float Y = 0.0f, float Rotation = 0.0f); //Default value was set to origin of the canvas.
	//Destructors
	~Transform();

	//methods
	/*
		Following three functions will provide convenience for calculation code in game programming.
	*/
	float DistanceTo(Transform target);
	float DistanceTo(float X, float Y);
	float AngleBetween(Transform target);

	/*
		To modify the transform easier, Transform class provides some member functions similar to human thinking way.
	*/
	void Move(Transform DeltaVector);
	void Move(float Dx, float Dy);
	void MoveTo(Transform toTarget);
	void MoveTo(float X, float Y);
	void Rotate(Transform target);
	void Rotate(float Dr);
	void Scale(float Factor);
	Transform Normalize();
	Transform Intersection(Transform t1, Transform t2, Transform t3, Transform t4);
	
	//Properties accessor
	void Set(float X, float Y, float Rotation);
	void SetXY(float X, float Y);
	void SetR(float Rotation);
	float getX();
	float getY();
	float getR();

private:
	float x;
	float y;
	float rotation;
	/*
		Rotation will be stored in this rule.
		90
	180		0
		270 
	*/

};

class Joint
{
	/*
		Joint class is the object for represent track joint. Joint will store the pointers to
		linked joints and tracks in the form of their pointer. Joint also have switch property,
		by using the Next() function, it will return the pointer to next track under current switch condition.
	*/
public:
	//Properties

	//Methods:
	/*
		Get next track under current switch condition
	*/
	Track* Next(Track* FromTrack);

	////***Constructor***//
	/*
		Different constructors are design for various condition when creating joint object.
	*/

	/*Default Constructor,
	Do NOT call this explicitly*/
	Joint();
	/*End Station Constructor*/
	Joint(Joint* NodeIn, Transform Transform);
	/*Begin Station Construcotr*/
	Joint(Joint* NodeOut0, Joint* NodeOut1, Transform Transform);
	/*Joint Constructor*/
	Joint(Joint* NodeIn, Joint* NodeOut0, Joint* NodeOut1, Transform Transform);

	////***Destructor***///
	~Joint();

	////***Properties***////

	//jID { set; get; }
	void setjointID(int JID);
	int getjointID();

	//Node { set; get; }
	void setNode0(Joint* Node);
	void setNode1(Joint* Node);
	void setNode2(Joint* Node);
	Joint* getNode0();
	Joint* getNode1();
	Joint* getNode2();

	//Track { set; get; }
	void setTrack0(Track* Track);
	void setTrack1(Track* Track);
	void setTrack2(Track* Track);
	Track* getTrack0();
	Track* getTrack1();
	Track* getTrack2();

	////***Properties END***///

	//Switch
	void changeSwitch(bool TS);
	void inverseSwitch();
	bool getTS();
	void setTS(bool TS);
	void lockTS(int CabKey, int CabKeyN);
	void unlockTS(int CabKey);

	Transform transform;

private:
	int jID;
	//Pointers to store the linked joints and tracks
	Joint* pnode0;
	Joint* pnode1;
	Joint* pnode2;

	Track* ptrack0;
	Track* ptrack1;
	Track* ptrack2;

	int tsLockA;
	int tsLockB;
	bool ts;
	//ts		trackSwitch
	/*
	Switch:	false:	Node0<->Node1
	true:	Node0<->Node2
	*/

};
class Track
{
	/*
		Track class is similar to joint class. It will store pointers to the
		linked joints. Next() function can return the the pointer to the next
		joint. Track class will store whether the track has roadblock or not.
	*/
public:
	//Properties

	//Methods
	Joint* Next(Joint* From);
	/*
		setupTransform will calculate the length and rotation of the track and 
		store it in member fields.
	*/
	void setupTransform();

	//Constructors
	Track();
	Track(Joint* node0, Joint* node1);

	//Destructors
	~Track();

	////***Properties***////
	//tID { set; get; }
	void settrackID(int TID);
	int gettrackID();

	//Joint { set; get; }
	void setJoint0(Joint* Node);
	void setJoint1(Joint* Node);
	Joint* getJoint0();
	Joint* getJoint1();

	//Length { private set; get;}
	float getLength();

	//hasRoadblock { set; get; }
	void sethasRb(bool HasRB);
	bool gethasRB();

	//roadBlock { set; get; }
	void setroadBlock(RoadBlock* RoadBlock);
	RoadBlock* getroadBlock();
	
	////***Properties END***////

	Transform transform;

private:
	int tID;
	float length;
	Joint* joint0;
	Joint* joint1;

	bool hasRoadBlock;
	RoadBlock* roadBlock;
};

class Train
{
	/*
		Train class is the object generally control the train, it contains several cabs
		object. Children object cabs are stored as pointer of array. Train object will not be
		directly display in game scene, but the cabs will be displayed. Train can move the cabs
		by passing the speed and delta-time between frames as arguments to the Move() function 
		in cab object. 
	*/
public:
	//Properties

	//Methods
	int Move(float DeltaTime);
	void Reverse();

	////***Constrcutors***////
	/*Default Constructor,
	Do NOT call this explicitly*/
	Train();
	/*Construt a Train object with 'cabsNumber' cabs*/
	Train(int cabsNumber, Transform transform);
	////***Destrcutors***////
	~Train();

	////***Properties***////

	//tID { set; get; }
	void settrainID(int TID);
	int gettrainID();

	//destination { set; get; }
	void setdestination(int Destination);
	int getdestination();

	//cabs { private set; get; }
	Cab * getcabs();

	//cabsNumber { private set; get; }
	int getcabsNumber();

	//speed { set; get; }
	void setSpeed(float Speed);
	float getSpeed();

	////***Properties END***////

private:
	int tID;
	int destination;
	Cab * cabs;
	Transform transform;
	int cabsNumber;
	float speed;
	bool inversed;
};

class Cab
{
	/*
		Cab class is the basic element of game object, it can move and rotate, they will
		be driven by train object. During most of time, this class will not be directly
		accessed.
	*/
public:
	//Properties

	//Methods
	int Move(float Speed, float DeltaTime);

	//Constructors
	/*Default Constructor,
	Do NOT call this explicitly*/
	Cab();

	//Destructors
	~Cab();

	////***Properties***////

	//cID { set; get; }
	void setcabID(int CID);
	int getcabID();

	//tID { set; get; }
	void settrainID(int TID);
	int gettrainID();
	
	//onTrack { set; get; }
	void setonTrack(Track* OnTrack);
	Track* getonTrack();

	//lastJoint( set; get; }
	void setlastJoint(Joint* Joint);
	Joint* getlastJoint();

	//cabLength { set; get; }
	void setcabLength(float CabLength);
	float getcabLength();

	//cabNumInTrain { set; get; }
	void setcabNumInTrain(int CabNumer);
	int getcabNumInTrain();

	////***Properties END***////
	Transform transform;

private:
	int cID;
	int tID;
	int cabNumInTrain;
	Track* onTrack;
	/*
		LastJoint pointer will store the passed joint and be used to retrive next track 
		form next joint's member function Next()
	*/
	Joint* lastJoint;
	/*
		cabLength is the interval between cabs, it will be used in train initialization.
	*/
	float cabLength;

	bool isHead;
};

class RoadBlock
{
	/*
		RoadBlock specify the roadblock element in game. It will store the radius and
		location in the track. It use onTrack pointer to store which track this roadblock
		is on.
	*/
public:
	//Properties

	//Methods
	/*
		SetupTrasform() function will calculate the specific location (x y coordinate in
		canvas). 
	*/
	void SetupTransform();

	//Constructors
	RoadBlock();
	/*
		Location is the percentage position on the track, therefore, GUI programmer can
		locate it easier. Radius will help the collision calculation to be more accurate
		and natural.
	*/
	RoadBlock(Track* onTrack, float Location, float Radius);
	//Destructors
	~RoadBlock();
	////***Properties***////

	//rbID
	void setroadBlockID(int RBID);
	int getroadBlockID();

	//Track
	void setonTrack(Track* OnTrack);
	Track* getonTrack();

	//location
	void setlocation(float Location);
	float getlocation();

	//radius
	void setradius(float Radius);
	float getradius();

	//blockState
	void setblockState(int BlockState);
	int getblockState();

	////***Properties END***////

	Transform transform;

private:
	int rbID;
	int tID;
	Track* onTrack;
	float location;
	float radius;
	int blockState;
};

