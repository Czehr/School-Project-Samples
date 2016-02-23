/* 
 * University of Central Florida
 * COP3330 - Spring 2016
 * Author: Chris Zehr, ch452589
 */
package jaccard;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

/**
 * 
 * @author glinosd
 */
public class Jaccard{
	
	List<SentenceUtils> sents;
	List<Set> shingleSets = new ArrayList<Set>(); /* Initialized shingleSets */
	
	public Jaccard(List<SentenceUtils> list ){
		
		sents = list;
		generateShingleSets();
	}
	
	private void generateShingleSets(){
		
		/* Loop through all sentences in list of SentenceUtils */
		for(SentenceUtils sentence : sents) {
			
			/* Create a set from the array of sentence shingles */
			Set<String> currentShingleSet = new HashSet<String>(Arrays.asList(sentence.getShingles()));
			
			/* Add shingle set to list of shingle sets */
			shingleSets.add(currentShingleSet);
		}
	}
	
	private double computeJaccard(Set<String> a, Set<String> b) {
		
		/* Get Set Intersection of 'a' and 'b' */
		Set<String> setIntersection = new HashSet<String>(a);
		setIntersection.retainAll(b);
		
		/* Get set Union of 'a' and 'b' */
		Set<String> setUnion = new HashSet<String>(a);
		setUnion.addAll(b);
		
		/* Return Jaccard Index of 'a' and 'b' */
		return (double)setIntersection.size() / (double)setUnion.size();
	}
	
	public void showSentenceStats() {

		/* For each sentence in list of SentenceUtils */
		for(SentenceUtils sentence : sents){
			/* Print sentence data */
			System.out.println("Sentence " + sents.indexOf(sentence) + ":" + "\n" +
							   "\t" + sentence.getSentence() + "\n" +
							   "\ttotal shingles: " + sentence.getShingles().length + "\n" +
							   "\tunique shingles: " + shingleSets.get(sents.indexOf(sentence)).size() + "\n");
		}
	}
	
	public void showSimilarities() {
		
		System.out.println("Jaccard Similarity Matrix:");
		
		/* For each combination of sentences */
		for (Set row : shingleSets)
		{
			for (Set col : shingleSets)
				/* Compute Jaccard index and print */
				System.out.printf("%.4f ", computeJaccard(row, col));
			
			/* Go to next line after each row */
			System.out.println("");
		}	
	}
}