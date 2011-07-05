#define NUM_PARTICLES    800          /* Number of particles  */
#define NUM_p2       400            /* Number of p2     */

class CExplosion {
public:
	CExplosion(int, int, int);
	~CExplosion();
	void continue_explosion();
	int x;
	int y;
	int z;
	int fuel;
private:
	float angle;
	struct particleData
	{
		float   position[3];
		float   speed[3];
		float   color[3];
	};
	typedef struct particleData    particleData;


/* A piece of p2 */

	struct p2Data
	{
	  float   position[3];
	  float   speed[3];
	  float   orientation[3];        /* Rotation angles around x, y, and z axes */
	  float   orientationSpeed[3];
	  float   color[3];
	  float   scale[3];
	};
	typedef struct p2Data    p2Data;
	void display_explosion();


	particleData     particles[NUM_PARTICLES];
	p2Data       p2[NUM_p2]; 
	
	void newSpeed (float dest[3]);
};