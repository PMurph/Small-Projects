package particles;

import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

import javax.media.opengl.GL2;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.glu.GLU;

import particles.math.Quaternion;
import particles.math.Vector;
import particles.objects.Particle;


@SuppressWarnings("serial")
public class ParticleCanvas extends GLCanvas implements GLEventListener, MouseMotionListener{
	private final static int INIT_WIDTH = 600, INIT_HEIGHT = 400;
	private final static float[] CLEAR_COLOUR = new float[] { 0.0f, 0.0f, 0.0f, 0.0f };
	private final GLU glUtils = new GLU();
	private final float FIELD_OF_VIEW = 45, DEFAULT_NEAR = 0.5f, DEFAULT_FAR = 5;
	private final float MAX_ROTATIONAL_SPEED = 0.1f;
	private final static int NUM_PARTICLES = 10;
	
	public final static float[] DEFUALT_FACE_COLOUR = new float[] { 0.5f, 0.5f, 0.5f, 1.0f };
	public final static float[] DEFAULT_OUTLINE_COLOUR = new float[] { 1.0f, 1.0f, 1.0f, 1.0f };
	public final static float DEFAULT_OUTLINE_WIDTH = 4.0f;
	public final static float DEFAULT_CAMERA_DISTANCE = 2.0f;
	public final static float DEFAULT_SIZE_OFFSET = 0.25f;
	
	private int width, height;
	private float aspect;
	private WorldBox worldBox;
	private CollisionDetector cDetect;
	private Quaternion cameraQuat, cameraUpQuat;
	private float deltaX, deltaY;
	private ArrayList<Particle> particles;
	
	public ParticleCanvas(GLCapabilities capab) {
		super(capab);
		
		initParticleCanvas();
	}
	
	/* ========================================================
	 * GLEventListener functions
	 * ========================================================
	 */
	
	public void init(GLAutoDrawable drawable) {
		final GL2 gl = drawable.getGL().getGL2();
		
		gl.glClearColor(CLEAR_COLOUR[0], CLEAR_COLOUR[1], CLEAR_COLOUR[2], CLEAR_COLOUR[3]);
		gl.glEnable(GL2.GL_CULL_FACE);
		gl.glCullFace(GL2.GL_BACK);
		gl.glEnable(GL2.GL_DEPTH_TEST);
		gl.glDepthFunc(GL2.GL_LEQUAL);
		
		particles = new ArrayList<>();
		worldBox = new WorldBox(0.0f, 0.0f, 0.0f, DEFAULT_CAMERA_DISTANCE + DEFAULT_SIZE_OFFSET, DEFAULT_CAMERA_DISTANCE + DEFAULT_SIZE_OFFSET, 
				DEFAULT_CAMERA_DISTANCE + DEFAULT_SIZE_OFFSET);
		cDetect = new CollisionDetector(worldBox);
		cameraQuat = new Quaternion(0.0f, 0.0f, 0.0f, -2.0f);
		cameraUpQuat = new Quaternion(0.0f, 0.0f, 1.0f, 0.0f);
		
		deltaX = 0.0f; deltaY = 0.0f;
		generateParticles();
		
		(new Timer()).scheduleAtFixedRate(new TimerTask() {
			public void run() {
				update();
				repaint();
			}
		}, 1000, 1000/60);
	}

	public void dispose(GLAutoDrawable drawable) {
		
	}

	public void display(GLAutoDrawable drawable) {
		final GL2 gl = drawable.getGL().getGL2();
		
		gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);
		
		setupProjection(gl);
		displayScene(gl);
	}

	public void reshape(GLAutoDrawable drawable, int x, int y, int width,
			int height) {
		final GL2 gl = drawable.getGL().getGL2();
		
		this.width = width;
		this.height = height;
		
		aspect = width /(float)(height == 0 ? 1: height);
		
		setupProjection(gl);
	}
	
	public void changeDelta(float deltaX, float deltaY)
	{
		this.deltaX = deltaX;
		this.deltaY = deltaY;
	}
	
	public void mouseDragged(MouseEvent e) {
		
	}

	public void mouseMoved(MouseEvent e) {
		int winX = e.getX(), winY = e.getY();
		int winWidth = this.getWidth(), winHeight = this.getHeight();

		deltaX = getDelta(winWidth, winX);
		deltaY = getDelta(winHeight, winY);
	}
	
	/* ========================================================
	 * Helper/Private functions
	 * ========================================================
	 */
	
	private void drawParticles(GL2 gl)
	{
		for(Particle part: particles)
		{
			part.draw(gl, glUtils);
		}
	}
	
	private float getDelta(int winDimension, int winPos)
	{
		float delta = 0.0f;
		int click, max;
		
		if(winPos > (3*winDimension / 4))
		{
			max = winPos - (3*winDimension / 4);
			click = winPos - (3*winDimension / 4);
			
			delta = click / (float)max;
		}
		else if(winPos < (winDimension / 4))
		{
			max = (winDimension / 4);
			click = winPos - (winDimension / 4);
			
			delta = click / (float)max;
		}
		
		return delta;
	}
	
	private void update()
	{
		rotateCamera();
		
		for(Particle part: particles)
		{
			part.moveParticle();
		}
	}
	
	private void rotateCamera()
	{
		float cameraXAngleChange = deltaX * MAX_ROTATIONAL_SPEED, cameraYAngleChange = deltaY * MAX_ROTATIONAL_SPEED;
		Vector horizontalAxis = cameraQuat.castToVector().cross(cameraUpQuat.castToVector());
		Quaternion temp;
		
		// Horizontal Camera Rotation
		temp = new Quaternion((float)Math.cos(cameraXAngleChange / 2.0f), cameraUpQuat.getX() * (float)Math.sin(cameraXAngleChange / 2.0f),
				cameraUpQuat.getY() * (float)Math.sin(cameraXAngleChange / 2.0f), cameraUpQuat.getZ() * (float)Math.sin(cameraXAngleChange / 2.0f) );
		
		cameraQuat = temp.multiply(cameraQuat);
		cameraQuat = new Quaternion(0.0f, cameraQuat.getX(), cameraQuat.getY(), cameraQuat.getZ());
		cameraQuat.normalize();
		cameraQuat.scalarMultiplication(DEFAULT_CAMERA_DISTANCE);
		
		cameraUpQuat = temp.multiply(cameraUpQuat);
		cameraUpQuat = new Quaternion(0.0f, cameraUpQuat.getX(), cameraUpQuat.getY(), cameraUpQuat.getZ());
		cameraUpQuat.normalize();
		
		temp = new Quaternion((float)Math.cos(cameraYAngleChange  /2.0f), horizontalAxis.getX() * (float)Math.sin(cameraYAngleChange / 2.0f), 
				horizontalAxis.getY() * (float)Math.sin(cameraYAngleChange / 2.0f), horizontalAxis.getZ() * (float)Math.sin(cameraYAngleChange / 2.0f));
		
		cameraQuat = temp.multiply(cameraQuat);
		cameraQuat = new Quaternion(0.0f, cameraQuat.getX(), cameraQuat.getY(), cameraQuat.getZ());
		cameraQuat.normalize();
		cameraQuat.scalarMultiplication(DEFAULT_CAMERA_DISTANCE);
		
		cameraUpQuat = temp.multiply(cameraUpQuat);
		cameraUpQuat = new Quaternion(0.0f, cameraUpQuat.getX(), cameraUpQuat.getY(), cameraUpQuat.getZ());
		cameraUpQuat.normalize();
		
	}
	
	private void initParticleCanvas()
	{
		width = INIT_WIDTH;
		height = INIT_HEIGHT;
		
		aspect = width / (float)height;
		
		this.addMouseMotionListener(this);
		this.addGLEventListener(this);
		this.setSize(width, height);
	}
	
	private void displayScene(GL2 gl)
	{
		gl.glMatrixMode(GL2.GL_MODELVIEW);
		gl.glLoadIdentity();
		
		glUtils.gluLookAt(-cameraQuat.getX(), -cameraQuat.getY(), -cameraQuat.getZ(), 0.0f, 0.0f, 0.0f, cameraUpQuat.getX(), cameraUpQuat.getY(), cameraUpQuat.getZ());

		gl.glColor3f(1.0f, 1.0f, 1.0f);
		
		worldBox.drawWorld(gl);
		drawParticles(gl);
				
		gl.glFlush();
	}
	
	private void setupProjection(GL2 gl)
	{
		gl.glMatrixMode(GL2.GL_PROJECTION);
		gl.glLoadIdentity();
		
		glUtils.gluPerspective(FIELD_OF_VIEW, aspect, DEFAULT_NEAR, DEFAULT_FAR);
	}
	
	private void generateParticles()
	{
		int i;
		Particle newParticle;
		
		for(i = 0; i < NUM_PARTICLES; i++)
		{
			newParticle = Particle.genRandParticle(worldBox);
			particles.add(newParticle);
			cDetect.registerParticle(newParticle);
		}
	}
}
