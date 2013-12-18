package particles;

import java.util.Timer;
import java.util.TimerTask;

import javax.media.opengl.GL2;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.glu.GLU;

import particles.math.Quaternion;
import particles.objects.Particle;


@SuppressWarnings("serial")
public class ParticleCanvas extends GLCanvas implements GLEventListener{
	private final static int INIT_WIDTH = 600, INIT_HEIGHT = 400;
	private final static float[] CLEAR_COLOUR = new float[] { 0.0f, 0.0f, 0.0f, 0.0f };
	private final GLU glUtils = new GLU();
	private final float FIELD_OF_VIEW = 45, DEFAULT_NEAR = 0.5f, DEFAULT_FAR = 5;
	private final float MAX_ROTATIONAL_SPEED = 0.1f;
	
	public final static float[] DEFUALT_FACE_COLOUR = new float[] { 0.5f, 0.5f, 0.5f, 1.0f };
	public final static float[] DEFAULT_OUTLINE_COLOUR = new float[] { 1.0f, 1.0f, 1.0f, 1.0f };
	public final static float DEFAULT_OUTLINE_WIDTH = 2.0f;
	public final static float DEFAULT_CAMERA_DISTANCE = 2.0f;
	
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
		
		worldBox = new WorldBox(0.0f, 0.0f, 0.0f, 2, 2, 2);
		testParticle = new Particle(0, 0, 0, 0.25f);
		cameraQuat = new Quaternion(0.0f, 0.0f, 0.0f, 2.0f);
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
	
	/* ========================================================
	 * Helper/Private functions
	 * ========================================================
	 */
	
	private void update()
	{
		rotateCamera();
	}
	
	private void rotateCamera()
	{
		float cameraXAngleChange = deltaX * MAX_ROTATIONAL_SPEED, cameraYAngleChange = deltaY * MAX_ROTATIONAL_SPEED;
		
		
	}
	
	private void initParticleCanvas()
	{
		width = INIT_WIDTH;
		height = INIT_HEIGHT;
		
		aspect = width / (float)height;
		
		this.addGLEventListener(this);
		this.setSize(width, height);
	}
	
	private void displayScene(GL2 gl)
	{
		gl.glMatrixMode(GL2.GL_MODELVIEW);
		gl.glLoadIdentity();
		
		glUtils.gluLookAt(cameraQuat.getX(), cameraQuat.getY(), cameraQuat.getZ(), 0.0f, 0.0f, 0.0f, cameraUpQuat.getX(), cameraUpQuat.getY(), cameraUpQuat.getZ());

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
