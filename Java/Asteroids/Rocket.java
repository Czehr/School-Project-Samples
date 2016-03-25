/*
 * University of Central Florida
 * COP3330 - Spring 2016
 * Author: Chris Zehr
 */
package asteroidgame;

import java.awt.event.KeyEvent;

import blobzx.BlobAction;
import blobzx.BlobProximity;
import blobzx.BlobUtils;
import blobzx.PolyBlob;
import blobzx.SandBox;
import java.awt.Point;


public class Rocket extends PolyBlob implements BlobAction, BlobProximity {
	
	//Required from Assignment
	private double angle = 0.0;
	private final double delta = 0.15; 
	private final double speed = 5.0;
	
	//My stuff
	private final int size = 11;
	private Point currentPoint, nextPoint, launchPoint;
	private SandBox sb;
	
	//Rocket Data, wide side is the front (think Batman)
	private int[] referenceRocketXArray = {4,  4, 2, 4, 4,   0, -3, 0, -3,  0,    4};
	private int[] referenceRocketYArray = {-10, -2, 0, 2, 10,   4,  2, 0, -2, -4,   -10};
	private int[] rocketXArray = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	private int[] rocketYArray = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	
	public Rocket(int x, int y, SandBox s) {
		super(0, 0, 0);
		
		sb = s;
		
		//Set initial location and angle
		setLoc(x, y);
		turn(0, size);
		
		//Create the rocket polygon
		setPolygon(rocketXArray, rocketYArray);
	}

	@Override
	public void keyAction(KeyEvent arg0) {
			
		switch(arg0.getKeyCode())
		{
			case 37: //turn left 
				angle -= delta; //Angles are already modular, so can turn two full rotations.
				turn(angle, 11);
				break;
			case 38: //boosters
				currentPoint = getLoc();
				nextPoint = BlobUtils.translatePoint(	currentPoint.x, 
														currentPoint.y, 
														speed, 
														angle);
				setLoc(nextPoint.x, nextPoint.y);
				break;
			case 39: //turn right
				angle += delta; //Angles are already modular, so can turn two full rotations.
				turn(angle, 11);
				break;
				
			case 32: //Spacebar
				launch(sb);
				BlobUtils.playSound();
				break;
		}

	}
	
	//Turns the rocket by angle "delta"
	public void turn(double delta, int size)
	{
		//for each point
		for(int i =0; i < size; i++)
		{	
			//Get the rotated point
			nextPoint = BlobUtils.rotatePoint(	referenceRocketXArray[i], 
												referenceRocketYArray[i], 
												delta);
			//Put the new point in the arrays
			rocketXArray[i] = (int)nextPoint.getX();
			rocketYArray[i] = (int)nextPoint.getY();
			
		}
	}
	
	public void launch(SandBox sb)
	{
		
		//Get location of missile spawn
		int launchDistance = (getSize()) / 2 + 5; // = 15
		
		//Get Current location
		currentPoint = getLoc();
		
		//Rotate missile spawn to front of rocket
		launchPoint = BlobUtils.rotatePoint(launchDistance, 0, angle);
		
		//Create a Missile
		Missile currentMissile = new Missile(currentPoint.x + launchPoint.x, currentPoint.y + launchPoint.y, angle);
		
		//Add the Missile to the SandBox
		sb.addBlob(currentMissile);
		
	}

}
