package particles.math;

public class Quaternion {
	private float w, x, y, z;
	
	public Quaternion(float w, float x, float y, float z)
	{
		this.w = w;
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	public Quaternion conjugate()
	{
		return new Quaternion(w, -x, -y, -z);
	}
	
	public Quaternion multiply(Quaternion other)
	{
		Quaternion product = new Quaternion(
				other.w * this.w - other.x * this.x - other.y * this.y - other.z * this.z,
				other.w * this.x + other.x * this.w - other.y * this.z + other.z * this.y,
				other.w * this.y + other.x * this.z + other.y * this.w - other.z * this.x,
				other.w * this.z - other.x * this.y + other.y * this.x + other.z * this.w
				);
		
		return product;
	}
	
	public Quaternion clone()
	{
		return new Quaternion(w, x, y, z);
	}
	
	public void normalize()
	{
		float sum = (float)Math.sqrt(w*w + x*x + y*y + z*z);
		
		w = w / sum;
		x = x / sum;
		y = y / sum;
		z = z / sum;
	}
	
	public float getW()
	{
		return w;
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
