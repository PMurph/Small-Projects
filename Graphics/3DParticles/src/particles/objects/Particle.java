package particles.objects;

import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;

import particles.CollisionDetector;
import particles.WorldBox;

public class Particle {
	private final static int DEFAULT_SLICES = 23;
	private final static int DEFAULT_STACKS = 23;
	private final static float DEFAULT_COLOUR[] = new float[] { 0.25f, 0.25f, 0.25f, 1.0f };
	private final static float MIN_RADIUS = 0.05f, MAX_RADIUS = 0.25f;
	private final static float MAX_VELOCITY = 0.05f;
	
	private float posX, posY, posZ;
	private float radius;
	private float velX, velY, velZ; // Velocity
	
	public Particle(float x, float y, float z, float radius)
	{
		this.posX = x;
		this.posY = y;
		this.posZ = z;
		
		this.radius = radius;
	}
	
	public void draw(GL2 gl, GLU glu)
	{
		GLUquadric sphere;
		
		gl.glPushMatrix();
		gl.glTranslatef(posX, posY, posZ);
		gl.glColor4f(DEFAULT_COLOUR[0], DEFAULT_COLOUR[1], DEFAULT_COLOUR[2], DEFAULT_COLOUR[3]);
		
		sphere = glu.gluNewQuadric();
		
		glu.gluQuadricDrawStyle(sphere, GLU.GLU_FILL);
		glu.gluQuadricNormals(sphere, GLU.GLU_FLAT);
		glu.gluQuadricOrientation(sphere, GLU.GLU_OUTSIDE);
		
		glu.gluSphere(sphere, radius, DEFAULT_SLICES, DEFAULT_STACKS);
		
		glu.gluDeleteQuadric(sphere);
		gl.glPopMatrix();
	}
	
	public void setVelocity(float x, float y, float z)
	{
		velX = x;
		velY = y;
		velZ = z;
	}
	
	public void moveParticle()
	{
		posX += velX;
		posY += velY;
		posZ += velZ;
	}
	
	public float getPosX()
	{
		return posX;
	}
	
	public float getPosY()
	{
		return posY;
	}
	
	public float getPosZ()
	{
		return posZ;
	}
	
	public float getRadius()
	{
		return radius;
	}
	
	public float getVelX()
	{
		return velX;
	}
	
	public float getVelY()
	{
		return velY;
	}
	
	public float getVelZ()
	{
		return velZ;
	}
	
	public void setVelX(float newVelX)
	{
		velX = newVelX;
	}
	
	public void setVelY(float newVelY)
	{
		velY = newVelY;
	}
	
	public void setVelZ(float newVelZ)
	{
		velZ = newVelZ;
	}
	
	public static Particle genRandParticle(WorldBox wBox, CollisionDetector cDetect)
	{
		Particle newParticle = null;
		float x, y, z, radius, velX, velY, velZ;
		
		do
		{
			radius = ((float)Math.random() * (MAX_RADIUS - MIN_RADIUS)) + MIN_RADIUS;
			x = ((float)Math.random()) * (wBox.getSizeX() - 2*radius) + wBox.getPosX();
			y = ((float)Math.random()) * (wBox.getSizeY() - 2*radius) + wBox.getPosY();
			z = ((float)Math.random()) * (wBox.getSizeZ() - 2*radius) + wBox.getPosZ();
			velX = ((float)Math.random() * (2 * MAX_VELOCITY)) - MAX_VELOCITY;
			velY = ((float)Math.random() * (2 * MAX_VELOCITY)) - MAX_VELOCITY;
			velZ = ((float)Math.random() * (2 * MAX_VELOCITY)) - MAX_VELOCITY;
			
			newParticle = new Particle(x, y, z, radius);
			newParticle.setVelocity(velX, velY, velZ);
		} while(cDetect.collisionWithParticle(newParticle));
		
		return newParticle;
	}
}
