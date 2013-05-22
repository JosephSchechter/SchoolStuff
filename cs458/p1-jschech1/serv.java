import java.io.*;
import java.net.*;


class serv {
	public static void main(String argv[]) throws Exception
	{
//		System.out.println("servin it up");
		
		if(argv.length != 1)
		{
			System.out.println("incorrect number of command line arguments, exiting\n (java serv <port_number>/n");
			return;
		}
		
		//trycatch example from oracle's website
		int portArg = 0;
		try {
			portArg = Integer.parseInt(argv[0]);
		} 
		catch (NumberFormatException e) {
			System.err.println("Argument must be an integer");
			System.exit(1);
		}
		
		ServerSocket listen = new ServerSocket(portArg);
		
		String clientSentence = "words";
		
//		System.out.println("before while loop");
		
		Process p;
		BufferedReader pIn;
		Runtime rt = Runtime.getRuntime();
		
		String FileNameBase = "";
		String seName = "";
		String sdName = "";
		
		String key = "security";
		int keyLength = key.length();
		String keyExpanded = "";
		String alph = "abcdefghijklmnopqrstuvwxyz";
		int alphLength = alph.length();
		char c;
		
		int ctLength;
		String pt;
		
		
		FileWriter fstream;
		BufferedWriter fout;
		
		
		while(true)
		{
//			System.out.println("in 1 while loop");
			Socket conn = listen.accept(); //connection
			BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
			
			PrintWriter out = new PrintWriter(conn.getOutputStream(),true);
			while(true)
			{
//				System.out.println("in 2 while loop");
				out.println("ftp> ");
				System.out.println("waiting for a read");
				clientSentence = in.readLine();
				System.out.println("FROM CLIENT:" + clientSentence);
				
				//client wants to quit
				if(clientSentence.equals("quit"))
				{
					break;
				}
				else if(clientSentence.length() < 3)
				{
					out.println("unknown command, try again");
					System.out.println("responded with \"unknown command, try again\"");
				}
				//client wants to run ls on his side
				else if(clientSentence.equals("lls") || clientSentence.equals("!ls"))
				{
					out.println("ls");
					System.out.println("responded with " + "ls");//let the client run it itself!
				}
				//client wants to run pwd on his side
				else if(clientSentence.equals("lpwd") || clientSentence.equals("!pwd"))
				{
					out.println("pwd");
					System.out.println("responded with " + "pwd");
				}
				//client wants to encrypt and upload a file to this server
				else if((clientSentence.substring(0,3)).equals("put"))
				{
					FileNameBase = clientSentence.substring(4); 
					//client decides if the file is acceptable, if not, will end this part
					clientSentence = in.readLine();
					if(clientSentence.equals("OK"))
					{
						//download the file <file_name>_ce
						clientSentence = in.readLine();
						
						//save <fn>_ce into <fn>_se
						seName = FileNameBase + "_se";
						try
						{
							// Create file 
							fstream = new FileWriter(seName);
							fout = new BufferedWriter(fstream);
							fout.write(clientSentence);
							//Close the output stream
							fout.close();
						}
						catch (Exception e){//Catch exception if any
							  System.err.println("Error: " + e.getMessage());
						}				
						
						//decrypt into <file_name>_sd
						sdName = FileNameBase + "_sd";
						ctLength = clientSentence.length();
						for(int i = 0; i < ctLength; i++)
						{
							keyExpanded = keyExpanded + key.substring(i%keyLength, (i%keyLength) + 1);
						}
							
						pt = "";
						for(int j = 0; j < ctLength; j++)
						{
							if((clientSentence.charAt(j)) >= (keyExpanded.charAt(j)))
							{
								pt = pt + (char)((((clientSentence.charAt(j)) - (keyExpanded.charAt(j))) % alphLength) + 97);
							}
							else
							{
								pt = pt + (char)( (clientSentence.charAt(j)) - (keyExpanded.charAt(j)) + 26 + 97);
							}
						}
						System.out.println("pt is: " + pt);
						
						
						//writing <fn>_sd
						try
						{
							// Create file 
							fstream = new FileWriter(sdName);
							fout = new BufferedWriter(fstream);
							fout.write(pt);
							//Close the output stream
							fout.close();
						}
						catch (Exception e){//Catch exception if any
							  System.err.println("Error: " + e.getMessage());
						}
						
						
						out.println("finished");
					
					}
					else //end if the file isnt ok
					{
						System.out.println("File not ok");
					}
					
				}
				//client types an unknown command
				else 
				{
					out.println("unknown command, try again");
					System.out.println("responded with \"unknown command, try again\"");
				}
				
			}
			//System.out.println("borked from inner while");
			
			conn.close();	//close connection w client
			System.out.println("If you want to quit the whole thing, press ctrl+c");
			
			//If you want to quit the whole thing, you could add a second break here, but thats not what we are interested in. we want the server to keep running, ending only when we press ctrl+c
		}
		
	}
}