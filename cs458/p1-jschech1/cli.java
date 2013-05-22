import java.io.*;
import java.net.*;


class cli {
	public static void main(String argv[]) throws Exception
	{
//		System.out.println("cliin it up");
		//System.out.println("arg0 = " + argv[0]);
		if(argv.length != 2)
		{
			System.out.println("incorrect number of command line arguments, exiting\n (java cli <server_machine> <server_port>/n");
			return;
		}
		
		//trycatch example from oracle's website
		int portArg = 0;
		try {
			portArg = Integer.parseInt(argv[1]);
		} 
		catch (NumberFormatException e) {
			System.err.println("Argument must be an integer");
			System.exit(1);
		}
		
		//connect to <server_machine> on port <server_port>
		Socket sock = new Socket(argv[0], portArg);

		//talking to server
		PrintWriter out = new PrintWriter(sock.getOutputStream(),true);
		BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
		String servWords = "things";
		String myWords = "lol";
		
		//user input
		BufferedReader reader;
		reader = new BufferedReader(new InputStreamReader(System.in));

		
		//PUT Stuff
		//samples from java-tips.org
		String fileNameBase = "input.txt";
		File file;
		FileInputStream fis = null;
		BufferedInputStream bis = null;
		DataInputStream dis = null;
		String readInFromFile = "";
		String ceName = "";
		String ct = "";
		String key = "security";
		int keyLength = key.length();
		String keyExpanded = "";
		int fileLength = 1;
		String alph = "abcdefghijklmnopqrstuvwxyz";
		int alphLength = alph.length();
		//char charAt = 'a';
		FileWriter fstream;
		BufferedWriter fout;
		
		
		//for running LS and PWD
		Process p;
		//BufferedReader pIn;
		DataInputStream pIn;
		Runtime rt = Runtime.getRuntime();
		String ls_str;
		
//		System.out.println("before while loop");
		
		while(true)
		{
//			System.out.println("in while loop");
			servWords = in.readLine();
			System.out.print(servWords + " "); //going to say ftp>
			myWords = reader.readLine();
			out.println(myWords);
			if(myWords.equals("quit"))//user types quit
			{
				break;
			}
			else if(myWords.length() < 3) //commands that are too short
			{
				servWords = in.readLine();
				System.out.println(servWords);
			}
			else if(myWords.equals("lls") || myWords.equals("!ls"))//user types lls
			{
				servWords = in.readLine();
				System.out.println(servWords);
				
				p = rt.exec("ls");
				pIn = new DataInputStream(p.getInputStream());

				
				//sampled from http://www.ensta.fr/~diam/java/online/io/javazine.html
				try {
					while ((ls_str = pIn.readLine()) != null)
					{
						System.out.println(ls_str);
					}
				}
				catch (IOException e)
				{
					System.exit(0);
				}			
				
			}
			else if(myWords.equals("lpwd") || myWords.equals("!pwd"))//user types lpwd
			{
				servWords = in.readLine();
				System.out.println(servWords);
				
				p = rt.exec("pwd");
				pIn = new DataInputStream(p.getInputStream());
				
				//sampled from http://www.ensta.fr/~diam/java/online/io/javazine.html
				try {
					while ((ls_str = pIn.readLine()) != null)
					{
						System.out.println(ls_str);
					}
				}
				catch (IOException e)
				{
					System.exit(0);
				}
				
			}
			else if((myWords.substring(0,3)).equals("put")) //they want to put something
			{
//				System.out.println("you said put");
				fileNameBase = myWords.substring(4);
//				System.out.println(fileNameBase);
				
				//client makes sure file exists and can be read
				//sampled from java-tips.org
				try {
					file = new File(fileNameBase);
					if(file.exists())
					{
						out.println("OK"); //the file exists
						
						fis = new FileInputStream(file);
						bis = new BufferedInputStream(fis);
						dis = new DataInputStream(bis);
						
						readInFromFile = "";
						//read in the file to a stream
						while (dis.available() != 0)
						{
							readInFromFile = readInFromFile + dis.readLine();
						}
						fis.close();
						bis.close();
						dis.close();
						
						keyExpanded = "";
						fileLength = readInFromFile.length();
						System.out.println("pt is " + readInFromFile);
						System.out.println("File length is " + fileLength + " chars");
						System.out.println("Key length is " + keyLength + " chars");
						//cipher the text
						for(int i = 0; i < fileLength; i++)
						{
							keyExpanded = keyExpanded + key.substring(i%keyLength, (i%keyLength) + 1);
						}
						System.out.println("Key expanded is :" + keyExpanded);
						
						ct = ""; //ciphertext
						for(int j = 0; j < fileLength; j++) //keyexp and readInFromFile are the same size
						{							
							ct = ct + (char)(((readInFromFile.charAt(j)-97 + keyExpanded.charAt(j)-97) % alphLength) + 97); //97 is ascii val of 'a'
//							System.out.println("ct = " + ct);
						}
						System.out.println("The cipher text is " + ct);
						
						//write <filename>_ce
						ceName = fileNameBase + "_ce";
						// sampled from http://www.roseindia.net/java/beginners/java-write-to-file.shtml 
						try
						{
							// Create file 
							fstream = new FileWriter(ceName);
							fout = new BufferedWriter(fstream);
							fout.write(ct);
							//Close the output stream
							fout.close();
						}
						catch (Exception e){//Catch exception if any
							  System.err.println("Error: " + e.getMessage());
						}
						
						
						//send <filename>_ce to server
						//<fn>_ce contains the same info as ct, so i can just send that to the server without having to re-extract the info
						out.println(ct);
						
						
						servWords = in.readLine();
						System.out.println(servWords);
						
					}
					else
					{
						System.out.println("file not found");
						out.println("NOT OK");
					}
				}
				catch (FileNotFoundException e){
					e.printStackTrace();
				}
				
			}
			else	//user types an unknown command
			{ 
				servWords = in.readLine();
				System.out.println(servWords);
			}
		}
		System.out.println("YOU'RE A QUITTER!");
		return;		
	}
}