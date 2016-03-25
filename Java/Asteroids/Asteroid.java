/*
 * University of Central Florida
 * COP3330 - Spring 2016
 * Author: Chris Zehr
 */

package asteroidgame;

import blobzx.PolyBlob;
import blobzx.BlobUtils;

import java.util.Random;
import java.awt.Point;
import java.lang.Math;
import java.util.ArrayList;


public class Asteroid extends PolyBlob {
	
	private static Random rand = new Random();
	private int numSides;
	private double region;
	Point currentPoint;
	
	ArrayList<Integer> polygonArrayX = new ArrayList<Integer>();
	ArrayList<Integer> polygonArrayY = new ArrayList<Integer>();
	
	public Asteroid(int x, int y, double r) {
		// PolyBlob()
		super(-100, -100, r);
		
		// Blob.setDelta()
		setDelta(x, y);
		
		// Random number of sides, and set region
		numSides = rand.nextInt(4) + 5;
		region = 2 * (Math.PI) / numSides;

		// Get location of each point
		for(int i = 0; i < numSides; i++)
		{
			currentPoint = BlobUtils.rotatePoint(	rand.nextInt(10) + 5,						// Diameter between 10 and 30
													(i * region) + (Math.random() * region )	// Point within region 
												);
			polygonArrayX.add(currentPoint.x);
			polygonArrayY.add(currentPoint.y);
		}
		
		//PolyBlob.setPolygon()
		setPolygon(integersToInts(polygonArrayX), integersToInts(polygonArrayY));
		
		
		
		
	}
	
	//Converts an ArrayList of Integers to an Array of ints
	public static int[] integersToInts(ArrayList<Integer> integers)
	{
	    int[] ints = new int[integers.size()];
	    
	    for (int i = 0; i < ints.length; i++)
	        ints[i] = integers.get(i).intValue();
	    
	    return ints;
	}

}
