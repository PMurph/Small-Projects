package particles;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLProfile;
import javax.swing.JFrame;

public class ParticleWindow extends JFrame {
	private final static String WINDOW_TITLE = "3D Particles Window";
	
	private ParticleCanvas partCanvas;
	
	public ParticleWindow()
	{
		super(WINDOW_TITLE);
		
		initWindow();
	}

	private void initWindow()
	{
		final GLProfile profile = GLProfile.get(GLProfile.GL2);
		final GLCapabilities capab = new GLCapabilities(profile);
		
		partCanvas = new ParticleCanvas(capab);
		
		this.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e)
			{
				System.exit(0);
			}
		});
		
		this.getContentPane().add(partCanvas);
		this.pack();
		this.setVisible(true);
	}
}
