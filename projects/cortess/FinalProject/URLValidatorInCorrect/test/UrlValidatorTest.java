

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	 UrlValidator urlVal =  new UrlValidator(null, null, 0);
	 System.out.println("Manual Test:");
//	 System.out.println(urlVal.isValid("http://www.google.com/home/destination"));
	 System.out.println(urlVal.isValid("http://0.0.0.0"));
//	 System.out.println(urlVal.isValidAuthority("256.256.256.256"));
   }
   
   
   public void testSchemePartition()
   {
	 //You can use this function to implement your First Partition testing
	 boolean expected = true;
	 List<String> failure = new ArrayList<String>();
	 UrlValidator urlVal = new UrlValidator(null, null, 0);
	 String testUrl = ""; 
	 
	 for(int i = 0; i < testScheme.length; i++) {
		 testUrl = testScheme[i].item + "www.google.com";
		 expected = testScheme[i].valid;
		 
		 if(urlVal.isValid(testUrl) != expected) {
			 failure.add(testScheme[i].item);
		 }
	 }
	 if(failure.size() > 0) {
		 System.out.println("Scheme partition failures: ");
		 System.out.println(failure);
	 }
   }
   
   public void testAuthorityPartition(){
	   //You can use this function to implement your Second Partition testing
	   boolean expected = true;
	   List<String> failure = new ArrayList<String>();
	   UrlValidator urlVal = new UrlValidator(null, null, 0);
	   String testUrl = "";
	   
	   for(int i = 0; i < testAuthority.length; i++) {
		   testUrl = "http://" + testAuthority[i].item;
		   expected = testAuthority[i].valid;
		   
		   if(urlVal.isValid(testUrl) != expected) {
			   failure.add(testAuthority[i].item);
		   }
	   }
	   if(failure.size() > 0) {		//Print list of failures if any
		   System.out.println("Authority partition failures:");
		   System.out.println(failure);
	   }
   }

   public void testPortPartition(){
	   //You can use this function to implement your Second Partition testing
	   boolean expected = true;
	   List<String> failure = new ArrayList<String>();
	   UrlValidator urlVal = new UrlValidator(null, null, 0);
	   String testUrl = "";
	   
	   for(int i = 0; i < testPort.length; i++) {
		   testUrl = "http://www.google.com" + testPort[i].item;
		   expected = testPort[i].valid;
		   
		   if(urlVal.isValid(testUrl) != expected) {
			   failure.add(testPort[i].item);
		   }
	   }
	   if(failure.size() > 0) {		//Print list of failures if any
		   System.out.println("Port partition failures:");
		   System.out.println(failure);
	   }
   }

   public void testPathPartition(){
	   //You can use this function to implement your Second Partition testing
	   boolean expected = true;
	   List<String> failure = new ArrayList<String>();
	   UrlValidator urlVal = new UrlValidator(null, null, 0);
	   String testUrl = "";
	   
	   for(int i = 0; i < testPath.length; i++) {
		   testUrl = "http://www.google.com" + testPath[i].item;
		   expected = testPath[i].valid;
		   
		   if(urlVal.isValid(testUrl) != expected) {
			   failure.add(testPath[i].item);
		   }
	   }
	   if(failure.size() > 0) {		//Print list of failures if any
		   System.out.println("Path partition failures:");
		   System.out.println(failure);
	   }
   }
   
   public void testQueryPartition(){
	   //You can use this function to implement your Second Partition testing
	   boolean expected = true;
	   List<String> failure = new ArrayList<String>();
	   UrlValidator urlVal = new UrlValidator(null, null, 0);
	   String testUrl = "";
	   
	   for(int i = 0; i < testQuery.length; i++) {
		   testUrl = "http://www.google.com" + testQuery[i].item;
		   expected = testQuery[i].valid;
		   
		   if(urlVal.isValid(testUrl) != expected) {
			   failure.add(testQuery[i].item);
		   }
	   }
	   if(failure.size() > 0) {		//Print list of failures if any
		   System.out.println("Query partition failures:");
		   System.out.println(failure);
	   }
   }

   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }


   public static void main(String[] args) {
	   UrlValidatorTest test = new UrlValidatorTest("Hello");
	   test.testManualTest();
	   test.testSchemePartition();
	   test.testAuthorityPartition();
	   test.testPortPartition();
	   test.testPathPartition();
	   test.testQueryPartition();
   }
   
   static ResultPair[] testScheme = {new ResultPair("http://", true),
		   new ResultPair("http:/", false),
		   new ResultPair("http//", false),
		   new ResultPair("ht://tp", false),
		   new ResultPair("://", false),
		   new ResultPair("", false)};

   static ResultPair[] testAuthority = {new ResultPair("www.google.com", true),
	              new ResultPair("google.com", true),
	              new ResultPair("www.google", false),
	              new ResultPair("google", false),
	              new ResultPair("0.0.0.0", true),
	              new ResultPair("0.0.0", false),
	              new ResultPair("0.0.0.0.0", false),
	              new ResultPair("255.255.255.255", true),
	              new ResultPair("256.256.256.256", false),
	              new ResultPair("", false)};
   
   static ResultPair[] testPort = {new ResultPair(":80", true),
	         new ResultPair(":65535", true),
	         new ResultPair(":65536", false),
	         new ResultPair(":-1", false),
	         new ResultPair(":", true),
	         new ResultPair(":0a", false),
	         new ResultPair("", true)};
   
   static ResultPair[] testPath = {new ResultPair("/home", true),
		  new ResultPair("/home/destination", true),
	      new ResultPair("/", true),
	      new ResultPair("/..", false),
	      new ResultPair("home", false),
	      new ResultPair("/home//destination", false),
	      new ResultPair("", true)};
	
   static ResultPair[] testQuery = {new ResultPair("?action=edit", true),
	          new ResultPair("?action=edit&mode=delete", true),
	          new ResultPair("?action=", true),
	          new ResultPair("=edit", false),
	          new ResultPair("", true)};
}

