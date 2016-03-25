/*
 * University of Central Florida
 * COP3330 - Spring 2016
 * Author: Chris Zehr
 */

package asteroidgame;

import blobzx.Blob;
import blobzx.BlobProximity;
import java.lang.Math;

public class Missile extends Blob implements BlobProximity {
	
	private double speed = 5;

	public Missile(int x, int y, double r) {
		super(x, y);
		
		//Calculate Missile velocity components
		int dx = (int) Math.round(speed * Math.cos(r) );
		int dy = (int) Math.round(speed * Math.sin(r) );
	
		// Blob.setDelta()
		setDelta(dx, dy);
				
	}

}
