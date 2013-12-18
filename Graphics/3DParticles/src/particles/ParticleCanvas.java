package particles;

import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
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
	private final static float DEFAULT_CAMERA_DISTANCE = 2.0f;
	private final static float DEFAULT_SIZE_OFFSET = 0.25f;
	
	public final static float[] DEFUALT_FACE_COLOUR = new float[] { 0.5f, 0.5f, 0.5f, 1.0f };
	public final static float[] DEFAULT_OUTLINE_COLOUR = new float[] { 1.0f, 1.0f, 1.0f, 1.0f };
	public final static float DEFAULT_OUTLINE_WIDTH = 4.0f;
	
	private int width, height;
	private float aspect;
	private WorldBox worldBox;
	private Particle testParticle; //TODO: this is just a test, remove later
	private Quaternion cameraQuat, cameraUpQuat;
	private float deltaX, deltaY;
	
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
		
		worldBox = new WorldBox(0.0f, 0.0f, 0.0f, DEFAULT_CAMERA_DISTANCE + DEFAULT_SIZE_OFFSET, DEFAULT_CAMERA_DISTANCE + DEFAULT_SIZE_OFFSET, 
				DEFAULT_CAMERA_DISTANCE + DEFAULT_SIZE_OFFSET);
		testParticle = new Particle(0, 0, 0, 0.25f);
		cameraQuat = new Quaternion(0.0f, 0.0f, 0.0f, -2.0f);
		cameraUpQuat = new Quaternion(0.0f, 0.0f, 1.0f, 0.0f);
		
		deltaX = 0.0f; deltaY = 0.0f;
		
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
		
		
		System.out.println("Horizontal Axis: " + horizontalAxis.getX() + ", " + horizontalAxis.getY() + ", " + horizontalAxis.getZ());
		/*
		System.out.println("Camera X angle change: " + cameraXAngleChange);
		System.out.println("Temp: " + temp.getW() + ", " + temp.getX() + ", " + temp.getY() + ", " + temp.getZ());
		System.out.println("Camera Quat: " + cameraQuat.getW() + ", " + cameraQuat.getX() + ", " + cameraQuat.getY() + ", " + cameraQuat.getZ());*/
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
		testParticle.draw(gl, glUtils);
				
		gl.glFlush();
	}
	
	private void setupProjection(GL2 gl)
	{
		gl.glMatrixMode(GL2.GL_PROJECTION);
		gl.glLoadIdentity();
		
		glUtils.gluPerspective(FIELD_OF_VIEW, aspect, DEFAULT_NEAR, DEFAULT_FAR);
	}

}
