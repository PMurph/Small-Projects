package particles.objects;

import javax.media.opengl.GL2;
import javax.media.opengl.glu.GLU;
import javax.media.opengl.glu.GLUquadric;

public class Particle {
	private final static int DEFAULT_SLICES = 23;
	private final static int DEFAULT_STACKS = 23;
	private final static float DEFAULT_COLOUR[] = new float[] { 0.25f, 0.25f, 0.25f, 1.0f };
	
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
}
