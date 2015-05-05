package compgeo.point.impl;

import compgeo.point.Point;
import compgeo.point.excpt.DimensionOutOfRangeException;
import compgeo.point.excpt.InvalidDimensionException;

public class BasicPoint implements Point {
	public static final int MIN_DIMENSION = 1;
	public static final String INVALID_DIMENSION_MESSAGE = "The dimension must be greater than or equal to " + String.valueOf(MIN_DIMENSION);
	public static final String DIMENSION_OUT_OF_RANGE = "The component dimension, %d, is not within the dimension of the point, %d.";
	
	private int dimension;
	private Number[] components;
	
	public BasicPoint(int dimension) throws InvalidDimensionException {
		if(dimension < MIN_DIMENSION) {
			throw new InvalidDimensionException(INVALID_DIMENSION_MESSAGE);
		}
		
		this.dimension = dimension;
		this.components = new Number[this.dimension];
		
		this.initComponents();
	}
	
	private void initComponents() {
		for(int i = 0; i < this.components.length; i++) {
			this.components[i] = new Integer(0);
		}
	}
	
	@Override
	public int getDimension() {
		return this.dimension;
	}

	public void setComponent(int componentDimension, Number value) throws DimensionOutOfRangeException {
		this.components[componentDimension] = value;
	}
	
	@Override
	public Number getComponent(int componentDimension) throws DimensionOutOfRangeException {
		if(componentDimension >= this.dimension) {
			throw new DimensionOutOfRangeException(String.format(this.DIMENSION_OUT_OF_RANGE, componentDimension, this.dimension));
		}
		
		return this.components[componentDimension];
	}

}
