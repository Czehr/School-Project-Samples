/*
 * University of Central Florida
 * COP330 - Spring 2016
 * Author: Chris Zehr, ch452589
 */
package jaccard;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class JaccardTest {
	
	private static List<SentenceUtils> slist = new ArrayList();
	
	public static void main(String[] args) {
		
		try {
			File file = new File( args[ 0 ]);
			
			Scanner scanner = new Scanner( new FileInputStream(file));
			
			while( scanner.hasNextLine() ){
				String sent = scanner.nextLine();
				if(sent.trim().length() > 0){
					SentenceUtils sutil = new SentenceUtils( sent );
					slist.add( sutil );
				}
			}
			scanner.close();
			
			System.out.println("\nJaccard Similarities by Chris Zehr\n");
			
			Jaccard jaccard = new Jaccard( slist );
			jaccard.showSentenceStats();
			jaccard.showSimilarities();
		}
		catch(FileNotFoundException e){
			e.printStackTrace();
		}
	}
}