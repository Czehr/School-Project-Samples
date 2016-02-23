/*
 * University of Central Florida
 * COP330 - Spring 2016
 * Author: Chris Zehr, ch452589
 */
package jaccard;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SentenceUtils {
	
	private List<String> tokenList = new ArrayList<String>();
	private List<String> shingleList = new ArrayList<String>();
	private Scanner scanner;
	
	private String sentence;
	private String[] tokens;
	private String[] shingles;
	
	public SentenceUtils( String s ){
		
		sentence = s;
		scanner = null;
		generateTokens();
		generateShingles(); 
	}

	private void generateTokens() {
		
		/* Create Scanner */
		scanner = new Scanner( sentence );
		
		/* Store tokens in ArrayList<String> */
		while( scanner.hasNext() )
			tokenList.add(scanner.next());
		
		/* Close Scanner */
		if(scanner != null)
			scanner.close();
		
		/* Convert ArrayList<String> to String[] */
		tokens = tokenList.toArray(new String[tokenList.size()]);	
	}
	
	private void generateShingles() {
		
		/* Store shingles of length 2 in ArrayList<String> */
		for(int i = 0; i < sentence.length() - 1; i++)
			shingleList.add(sentence.substring(i, i + 2));
		
		/* Convert ArrayList<String> to String[] */
		shingles = shingleList.toArray(new String[shingleList.size()]);
	}

	public void report(){
		
		System.out.println(sentence);
		
		/* Print tokens with index on each line */
		for(int i = 0; i < tokens.length; i++)
			System.out.println(i + ":" + tokens[i]);
		
		/* Print space separated shingles */
		for(String s : shingles)
			System.out.print(s + " ");
		
		/* Separate each sentence report */
		System.out.println("\n");
	}
	
	public String getSentence() {
		return sentence;
	}
	
	public String[] getShingles()
	{
		return shingles;
	}
}