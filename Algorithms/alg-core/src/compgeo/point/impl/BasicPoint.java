package compgeo.point.impl;

import compgeo.point.Point;
import compgeo.point.excpt.InvalidDimensionException;

public class BasicPoint<E> implements Point<E> {
	public static final int MIN_DIMENSION = 1;
	public static final String INVALID_DIMENSION_MESSAGE = "The dimension must be greater than or equal to " + String.valueOf(MIN_DIMENSION);
	
	private int dimension;
	
	public BasicPoint(int dimension) throws InvalidDimensionException {
		this.dimension = dimension;
		
		if(dimension < MIN_DIMENSION) {
			throw new InvalidDimensionException(INVALID_DIMENSION_MESSAGE);
		}
	}
	
	public int getDimension() {
		return this.dimension;
	}

	@Override
	public E getComponent(int dimension) {
		// TODO Auto-generated method stub
		return null;
	}

}
