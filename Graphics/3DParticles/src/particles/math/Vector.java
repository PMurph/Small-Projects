package particles.math;

public class Vector {
	private float x, y, z;
	
	public Vector(float x, float y, float z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	public Vector cross(Vector other)
	{
		return new Vector(
				y * other.getZ() - z * other.getY(), 
				z * other.getX() - x * other.getZ(),
				x * other.getY() - y * other.getX());
	}
	
	public Quaternion castToQuat()
	{
		return new Quaternion(0, x, y, z);
	}
	
	public float getX()
	{
		return x;
	}
	
	public float getY()
	{
		return y;
	}
	
	public float getZ()
	{
		return z;
	}
}
