package particles.objects;

public class Particle {
	private float posX, posY, posZ;
	private float sizeX, sizeY, sizeZ;
	private float velX, velY, velZ; // Velocity
	
	public Particle(float x, float y, float z, float sizeX, float sizeY, float sizeZ)
	{
		this.posX = x;
		this.posY = y;
		this.posZ = z;
		
		this.sizeX = sizeX;
		this.sizeY = sizeY;
		this.sizeZ = sizeZ;
	}
}
