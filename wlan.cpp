#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string>
#include <time.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;








char buffer[99999]; 
size_t pos1;
size_t pos2;
bool joined = false;
int random_integer;
string asd;
string pong;
string channel;
string channel2;
string user;
string nick;
string rlmsg;
string rlmsghlp;
string msg;
string msgnick;
string hostname;
stringstream ConvertStream;
string randi;
string currchan;
string currchan_final;
 int fd; 
  


  

void swap(char* first, char* second)
{
        char ch = *second;
        *second = *first;
        *first = ch;
}




int permute(char* set, int begin, int end)
{
        int i;
        int range = end - begin;
        if (range == 1) {
                cout << set << endl;
msg = "PRIVMSG " + currchan_final + " :" + set + "\r\n";
			 send(fd,msg.c_str(), msg.length(),0);
        } else {
                for(i=0; i<range; i++) {
                        swap(&set[begin], &set[begin+i]);		//initial swap
                        permute(set, begin+1, end);				//recursion
                        swap(&set[begin], &set[begin+i]);       //swap back
                }
        }
        return 0;
}










/////////////////////////////////////////////////////////////////////////////////////////multi channel support incoming currentchan :E!
//main
int main()
{
channel = "#wlan";
channel2 = "#joulu";
nick = "NICK wlan-bot\r\n";
user = "USER wlan wlan wlan wlan wlan\r\n";
system("clear");
cout << "Wlan-bot started!\r\n\r\n";
cout << "Wlan-bot, made by Niko-\r\n";
cout << "irc.joulunet.org --> #joulu, #wlan\r\n";

	

	//main try ()
	try {


	struct sockaddr_in sa; 

	if (( fd = socket ( PF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0 ){
		perror("Error in socket");} 
 
	memset ( &sa, 0, sizeof ( sa )); 
	sa.sin_family = AF_INET; 
	sa.sin_port = htons ( 6667 ); 
	sa.sin_addr.s_addr = inet_addr ( "88.195.12.222" ); 
 
	
	if ( connect ( fd, (struct sockaddr *)&sa, sizeof ( sa )) < 0 ){
		perror("Error while connecting");}
 	if(joined == false)
	{
	sleep(2);
          send (fd,user.c_str(),user.length(),0);
          cout << (user + "\r\n");
          sleep(2);
          send (fd,nick.c_str(),nick.length(),0);
          cout << (nick + "\r\n");
	if(joined == false)
			 {
	sleep(5);
        string join = "JOIN " + channel + "\r\n";
        send(fd,join.c_str(), join.length(),0);
        /*string join2 = "JOIN " + channel2 + "\r\n";
        send(fd,join2.c_str(), join2.length(),0);*/
        joined = true;
			 }

	}
	//while true looppi
	while(fd)
        {
        memset(buffer,0,sizeof(buffer));
        recv(fd, buffer, sizeof(buffer), 0);
        cout << (buffer);
        asd = buffer;
        
	
	/* if(asd.substr(20, 3) == "376")             //(asd.substr(20, 3) == "376")//end of motd    55
          {
          cout << ("END OF MOTD->Joining\r\n");
                    if(joined == false)
			 {
        string join = "JOIN " + channel + "\r\n";
        send(fd,join.c_str(), join.length(),0);
        //string join2 = "JOIN " + channel2 + "\r\n";
        //send(fd,join2.c_str(), join2.length(),0);
        joined = true;
			 }
          }      
         else */
	
		if(asd.substr(0,4) == "PING")
        	 {   
	try {
       	 pong = asd.replace(0,4,"PONG");
            
       	 send(fd,pong.c_str(), pong.length(),0);
       	 cout << (pong.c_str());
	}
       catch(...) 
	{
      	cout << "Exception raised \n";
  	}
      	   	 } 
	



        if(joined == true)
        {
		//nicknamesplitter
			msgnick = asd.substr(1,asd.find_first_of("!") -1);
			//hostnamesplitter
		/*	
			int host1 = asd.find_first_of("~");
			int host2 = asd.find_first_of(' ');
			string segs = asd.substr(host1,host2);
			hostname = asd.substr(host1,host2 - msgnick.length() - 2);*/
			
			//:eth3!~nieminen@dsl-hkibrasgw2-fe4fde00-251.dhcp.inet.fi PRIVMSG #toppeli :testi

			
        //msgsplitter               
        pos1 = asd.find_first_of(":");
        rlmsghlp = asd.substr(pos1 +  1);
			
        pos2 = rlmsghlp.find_first_of(":");
        rlmsg = rlmsghlp.substr(pos2 + 1);
        cout << ("<"+msgnick+">" + rlmsg + "\r\n");


		//channelsplitter
		try
		{
		currchan = asd.substr(asd.find_first_of("#"));
		//cout << currchan + "\r\n";
		currchan_final = currchan.substr(0, currchan.find_first_of(":") - 1);
		//cout << currchan_final + "\r\n";
		}
		catch(...) 
		{
      		cout << "Exception raised \n";
  		}


        }



       
        


//iffittelyä
		if(joined == true)
        {
	
	/*if(rlmsg.find("wlan") != -1)
	{
	msg = "PRIVMSG " + currchan_final + " :;D\r\n";
        send(fd,msg.c_str(), msg.length(),0);
	}		
        else*/ if(rlmsg == "wlan\r\n")
        {
        msg = "PRIVMSG " + currchan_final + " :;D\r\n";
        send(fd,msg.c_str(), msg.length(),0);
        }
	    else if(rlmsg == ";D\r\n")
			{
			msg = "PRIVMSG " + currchan_final + " :wlan ;D\r\n";
            send(fd,msg.c_str(), msg.length(),0);
				
			}
		else if(rlmsg == "wlan ;D\r\n")
			{
			msg = "PRIVMSG " + currchan_final + " :;D\r\n";
            send(fd,msg.c_str(), msg.length(),0);	
			}
		else if(rlmsg == "ubuntu server ja wlan\r\n")
			{
			msg = "PRIVMSG " + currchan_final + " :;D\r\n";
            send(fd,msg.c_str(), msg.length(),0);	
			}
		else if(rlmsg == "ubuntu server ja wlan ;D\r\n")
			{
			msg = "PRIVMSG " + currchan_final + " :;D\r\n";
            send(fd,msg.c_str(), msg.length(),0);	
			}
		else if(rlmsg == "aivan yllättäen\r\n")
			{
			msg = "PRIVMSG " + currchan_final + " :WLAN! ;DDDDDD\r\n";
            send(fd,msg.c_str(), msg.length(),0);	
			}
	        else if(rlmsg == "fail\r\n")
			{
			msg = "PRIVMSG " + currchan_final + " :wlan never fails ;D\r\n";
            send(fd,msg.c_str(), msg.length(),0);	
			}
	    else if(rlmsg == "!time\r\n")
			{
			time_t too = time(0);
				time_t rawtime;
			struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );

			msg = "PRIVMSG " + currchan_final + " :" + asctime(timeinfo) + "\r\n";
            send(fd,msg.c_str(), msg.length(),0);
			}
		else if(rlmsg == "!rand\r\n")
			{
				srand(time(NULL));
				
                int number1 = 0;
                
                number1 = rand();
			//memset (ConvertStream, 0, sizeof(ConvertStream));
			ConvertStream  << number1;
            // ConvertStream >> randi;
				
			 msg = "PRIVMSG " + currchan_final + " :" + ConvertStream.str() + "\r\n";
			 send(fd,msg.c_str(), msg.length(),0);
			}
		else if(rlmsg.substr(0,6) == "!write")
			{
				if(msgnick == "Niko-" || msgnick=="Teppo")
				{
				string sub = rlmsg.substr(7); //korjaa tää
				send(fd,sub.c_str(), sub.length(),0);
				}	
			}
		/*else if(rlmsg.substr(0,5) == "!exec")
			{
				if(msgnick=="peehoopee" || msgnick=="antispam" || msgnick == "eth3")
				{			
				string returni;
				string komento = rlmsg.substr(6);
				string komento2 = komento.erase(komento.length()-2,komento.length());
				string komento3 = komento2 + " > temp.txt &";
				
				system(komento3.c_str());
					ifstream tempfile ("temp.txt"); //////JATKA SÄÄTÖÄ TÄSTÄ NÄIN!!!_-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-__-_-_-_-_
					if (tempfile.is_open())
                    {
                    while (! tempfile.eof() )
                    {
                        getline (tempfile,returni);
                           msg = "PRIVMSG " + channel + " :" + komento2 + " :" + returni + "\r\n";
			               send(fd,msg.c_str(), msg.length(),0);
                    }
                   tempfile.close();
						remove("temp.txt");
						ofstream myfile;
                  myfile.open ("temp.txt");
                  myfile << "Output :\n";
                  myfile.close();

                    }
					else
					{
						msg = "PRIVMSG " + channel + " :" + komento2 + " :error..\r\n";
			            send(fd,msg.c_str(), msg.length(),0);
					}

					
				}
				else
				{
				msg = "PRIVMSG " + channel + " :You don't have permission to access this feature!\r\n";
			 send(fd,msg.c_str(), msg.length(),0);	
				}
			}*/
		else if(rlmsg.substr(0,5) == "!exec")
				{
					
				if(msgnick=="Niko-" || msgnick=="Teppo")
				{			
				string komento = rlmsg.substr(6);
				
				string komento2 = komento.erase(komento.length()-2,komento.length());
						
	
					 FILE *fp;
                char line[130];			/* line of data from unix command*/
   
               fp = popen(komento2.c_str(), "r");		/* Issue the command.		*/

					/* Read a line			*/
               while ( fgets( line, sizeof line, fp))
                {
                 // printf("%s", line);
					msg = "PRIVMSG " + currchan_final + " :" + line + "\r\n";
			            send(fd,msg.c_str(), msg.length(),0);
					sleep(2);
                }
                 pclose(fp);
					
			
					
				}

					
					
					
					
				}
		else if(rlmsg == "!wlanquit\r\n")
			{
			if(msgnick=="Niko-" || msgnick=="Teppo")
				{
					return 0;
				}
			}
		else if(rlmsg == "!wlaninfo\r\n")
			{
				msg = "PRIVMSG " + currchan_final + " :wlan tuo pienet pingit ;D, for more info visit http://vhost.fi/wlan\r\n";
			 send(fd,msg.c_str(), msg.length(),0);	
			}
		else if(rlmsg.substr(0,6) == "!permu")
			{
				if(msgnick == "Niko-" || msgnick == "Teppo")
				{
                     char str[255];
				       //str = rlmsg.substr(7);
				string tremp1 = rlmsg.substr(7);
				string tremp2 = tremp1.erase(tremp1.length()-2,tremp1.length());
				     strcpy(str, tremp2.c_str());
                      permute(str, 0, strlen(str)); //permutate the string

			
				}
			}
			else if(rlmsg.substr(0,6) == "!permu")
			{
				
				
			} //
	
		

			
        }

        
        
        }
        //
	//endofmain TRY
	}
	catch(...) 
	{
      		cout << "Exception raised: \n";
		
  	}




return 0;

	
	
	
	
	
	
	
	
	
}







