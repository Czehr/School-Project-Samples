/*
 * University of Central Florida
 * COP3330 - Spring 2016
 * Author: Chris Zehr
 */

package asteroidgame;


import blobzx.BlobGUI;
import blobzx.SandBox;
import blobzx.SandBoxMode;
import java.util.Random;

public class AsteroidGame implements BlobGUI{

	private SandBox asteroidGameSandBox;
	private Random rand = new Random();
	
	
	public static void main(String[] args) {
		AsteroidGame testGame = new AsteroidGame();
	}
	
	
	public AsteroidGame() {
		/* 
		 (i) create a sandbox object;

	     (ii) set the sandbox to "flow" mode;

	     (iii) set the sandbox to run at 15 frames per second; and

	     (iv) Run the sandbox’s	new	init() method this way:	<sandboxInstance>.init(	this );	
	     
		*/
		
		asteroidGameSandBox = new SandBox();
	    
		asteroidGameSandBox.setSandBoxMode(SandBoxMode.FLOW);
		
		asteroidGameSandBox.setFrameRate(15);
		
		asteroidGameSandBox.init(this);
		
		
	}

	@Override
	public void generate() {
		
		//Create a rocket
		Rocket testRocket = new Rocket(300,300, asteroidGameSandBox);
		
		//Add rocket to sandbox
		asteroidGameSandBox.addBlob(testRocket);
		
		
		/*
		
		(i) it must create 10 asteroids using the velocity components and rotational values described here;

     	(ii) it must randomly choose x and y velocity components for each asteroid, where the x and y components 
     		 are chosen independently of each other and where each of these values is an integer that may range
     		 from -3 to +3, but where zero values are disallowed, all as discussed in lecture;

     	(iii) it must randomly choose a rotation value of either -.1 or +.1 for each asteroid, with equal 
     		  probability. Values in between -.1 and +.1 are not permitted; and

     	(iv) it must add each asteroid to the sandbox.
		*/
		
		int xVelocity = 0;
		int yVelocity = 0;
		int magnitude;
		double rotation = .1;
		
		
		//For each asteroid
		for(int i = 0; i < 10; i++)
		{
			//For both vectors
			for(int j = 0; j < 2; j++)
			{
				magnitude = rand.nextInt(2) + 1;	//Get Random magnitude 0-3
				if(rand.nextBoolean())				
					magnitude *= -1;				//Point vector in random direction
				if(j == 0)
					yVelocity = magnitude;			//Set y component vector
				else
					xVelocity = magnitude;			//Set x component vector
			}	
			if(rand.nextBoolean())
				rotation *= -1;						//Set rotation randomly
					
			//Create an Asteroid
			Asteroid currentAsteroid = new Asteroid(xVelocity, yVelocity,rotation);
			
			//Add the Asteroid to the SandBox
			asteroidGameSandBox.addBlob(currentAsteroid);
		}
	}

}
