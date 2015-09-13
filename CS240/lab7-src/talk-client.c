


#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
int cs = 0;
int au = 0;//for checking no. of users
int mm = 0;//for checking no. of messages
  char *value;
char *text;
int nr = 0;
char * args;
char * host;
char * user;
char * password;
char * sport;
char * tep;
int port;
GtkWidget *username;
GtkWidget *pass;
    GtkWidget *list;
    GtkWidget *messages;
    GtkWidget *myMessage;
	GtkWidget *userlist;
	GtkWidget *ulist;
GtkListStore * list_rooms;
GtkTreeSelection * selection;
GtkWidget *tree_view;
GtkListStore * list_user;
	GtkWidget *rooms;
    GtkWidget *window;
GtkWidget *mlist;
GtkListStore * list_messages;
#define MAX_MESSAGES 100
#define MAX_MESSAGE_LEN 300
#define MAX_RESPONSE (20 * 1024)



int lastMessage = 0;

int open_client_socket(char * host, int port) {
	// Initialize socket address structure
	struct  sockaddr_in socketAddress;
	
	// Clear sockaddr structure
	memset((char *)&socketAddress,0,sizeof(socketAddress));
	
	// Set family to Internet 
	socketAddress.sin_family = AF_INET;
	
	// Set port
	socketAddress.sin_port = htons((u_short)port);
	
	// Get host table entry for this host
	struct  hostent  *ptrh = gethostbyname(host);
	if ( ptrh == NULL ) {
		perror("gethostbyname");
		exit(1);
	}
	
	// Copy the host ip address to socket address structure
	memcpy(&socketAddress.sin_addr, ptrh->h_addr, ptrh->h_length);
	
	// Get TCP transport protocol entry
	struct  protoent *ptrp = getprotobyname("tcp");
	if ( ptrp == NULL ) {
		perror("getprotobyname");
		exit(1);
	}
	
	// Create a tcp socket
	int sock = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}
	
	// Connect the socket to the specified server
	if (connect(sock, (struct sockaddr *)&socketAddress,
		    sizeof(socketAddress)) < 0) {
		perror("connect");
		exit(1);
	}
	
	return sock;
}

int sendCommand(char * host, int port, char * command, char * user,
		char * password, char * args, char * response) {
	int sock = open_client_socket( host, port);

	// Send command
	write(sock, command, strlen(command));
	write(sock, " ", 1);
	write(sock, user, strlen(user));
	write(sock, " ", 1);
	write(sock, password, strlen(password));
	write(sock, " ", 1);
	write(sock, args, strlen(args));
	write(sock, "\r\n",2);

	// Keep reading until connection is closed or MAX_REPONSE
	int n = 0;
	int len = 0;
	while ((n=read(sock, response+len, MAX_RESPONSE - len))>0) {
		len += n;
	}
	response[len] = '\0';
 	
	printf("response:%s\n", response);

	close(sock);
}//till here

void add_user() {
	// Try first to add user in case it does not exist.
	char response[ MAX_RESPONSE ];
	au++;
	sendCommand(host, port, "ADD-USER", user, password, " ", response);
	if (!strcmp(response,"OK\r\n")) {
		printf("User %s added\n", user);
	}
	if (!strcmp(response,"DENIED\r\n")) {
		printf("User %s is logged in\n", user);
	}
}
static void hello2( GtkWidget *widget,
                   gpointer   data )

{
	int i = 0;
	const gchar *entry_text; //works on pressing enter
	  entry_text = strdup(gtk_entry_get_text (GTK_ENTRY (username)));  		
		user = strdup(gtk_entry_get_text (GTK_ENTRY (username)));		
	//user = strdup(entry_text);
	//char * lax = (char*)malloc(50*sizeof(char));
	//char * lax2 = (char*)malloc(50*sizeof(char));	
    //lax = strdup(gtk_entry_get_text (GTK_ENTRY (arr[0])));    
	//lax2 = strdup(gtk_entry_get_text (GTK_ENTRY (arr[1])));
    printf("user is %s\n",user);
	const gchar *entry_text1;
	entry_text = strdup(gtk_entry_get_text (GTK_ENTRY (pass)));  		
	password = strdup(gtk_entry_get_text (GTK_ENTRY (pass))); 	
	printf("password is %s\n",password);
	
	const gchar *ent;
	ent = strdup(gtk_entry_get_text (GTK_ENTRY (rooms))); 
	args = strdup(gtk_entry_get_text (GTK_ENTRY (rooms)));
		
    printf("Room is %sfgh\n",args);
leave_room();
	g_print ("SignUp\n");
	
}
static void hello3( GtkWidget *widget,
                   gpointer   data )

{
	int i = 0;
	const gchar *entry_text; //works on pressing enter
	  entry_text = strdup(gtk_entry_get_text (GTK_ENTRY (username)));  		
		user = strdup(gtk_entry_get_text (GTK_ENTRY (username)));		
	//user = strdup(entry_text);
	//char * lax = (char*)malloc(50*sizeof(char));
	//char * lax2 = (char*)malloc(50*sizeof(char));	
    //lax = strdup(gtk_entry_get_text (GTK_ENTRY (arr[0])));    
	//lax2 = strdup(gtk_entry_get_text (GTK_ENTRY (arr[1])));
    printf("user is %s\n",user);
	const gchar *entry_text1;
	entry_text = strdup(gtk_entry_get_text (GTK_ENTRY (pass)));  		
	password = strdup(gtk_entry_get_text (GTK_ENTRY (pass))); 	
	printf("password is %s\n",password);
		
gtk_list_store_clear(GTK_LIST_STORE(list_rooms));
update_list_rooms();
	g_print ("SignUp\n");
	
}
// * //;
char resp[ MAX_RESPONSE ];
void send_message(char * msg) {
char * tue = (char *)malloc(100*sizeof(char));
tue = strdup(tep);
strcat(tue," ");
strcat(tue,msg);
int len = strlen(tue);
printf("sent len is %d\n",len);
char response[ MAX_RESPONSE ];
sendCommand(host,port,"SEND-MESSAGE",user,password,tue,response);
if(!strcmp(response,"OK\r\n"))
{
printf("MESSAGE SENT\n");
mm++;
}
}






const gchar *entry_text; 
static void hello( GtkWidget * widget,
				    GtkWidget * data)//gpointer data )
{
	int i = 0;
	//const gchar *entry_text; //works on pressing enter
	  entry_text = strdup(gtk_entry_get_text (GTK_ENTRY (data)));  		
		user = strdup(gtk_entry_get_text (GTK_ENTRY (data)));		
	//user = strdup(entry_text);
	//char * lax = (char*)malloc(50*sizeof(char));
	//char * lax2 = (char*)malloc(50*sizeof(char));	
    //lax = strdup(gtk_entry_get_text (GTK_ENTRY (arr[0])));    
	//lax2 = strdup(gtk_entry_get_text (GTK_ENTRY (arr[1])));
    printf("user is %s\n",user);
	const gchar *entry_text1;
	entry_text = strdup(gtk_entry_get_text (GTK_ENTRY (pass)));  		
	password = strdup(gtk_entry_get_text (GTK_ENTRY (pass))); 	
	printf("password is %s\n",password);	
	//printf("lax2 is %s\n",lax2);
	//strcat(lax," ");	
	//user = strdup(lax);
	//password = strdup(lax2);
	//host = "localhost";
    //port = 2011; 
    add_user();
	g_print ("SignUp\n");
	
}
static void hello1( GtkWidget * widget,
				    GtkWidget * data)//gpointer data )
{
	int i = 0;
	//const gchar *entry_text; //works on pressing enter
	  entry_text = strdup(gtk_entry_get_text (GTK_ENTRY (username)));  		
		user = strdup(gtk_entry_get_text (GTK_ENTRY (username)));		
	//user = strdup(entry_text);
	//char * lax = (char*)malloc(50*sizeof(char));
	//char * lax2 = (char*)malloc(50*sizeof(char));	
    //lax = strdup(gtk_entry_get_text (GTK_ENTRY (arr[0])));    
	//lax2 = strdup(gtk_entry_get_text (GTK_ENTRY (arr[1])));
    printf("user is %s\n",user);
	const gchar *entry_text1;
	entry_text = strdup(gtk_entry_get_text (GTK_ENTRY (pass)));  		
	password = strdup(gtk_entry_get_text (GTK_ENTRY (pass))); 	
	printf("password is %s\n",password);
	
	const gchar *ent;
	ent = strdup(gtk_entry_get_text (GTK_ENTRY (data))); 
	args = strdup(gtk_entry_get_text (GTK_ENTRY (data)));
		
    printf("Room is %sfgh\n",args);
    create_room();
	g_print ("SignUp\n");
	
}
//GtkListStore * list_rooms;

void update_list_rooms() {
    GtkTreeIter iter;
    int i;
	

	//list_room();
	char response[ MAX_RESPONSE ];
	sendCommand(host, port, "LIST-ROOMS", user, password, " ", response);
	printf("Response is %s\n",response);
	gchar *msg = g_strdup_printf(strtok(response,"\r\n"));
	if(msg == NULL)	
	{
		return;
	}
	printf("msg is %s\n",msg);
	gtk_list_store_append (GTK_LIST_STORE (list_rooms), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_rooms), 
	                    &iter,
                            0, msg,
	                    -1);
	
	while((msg = g_strdup_printf(strtok(NULL,"\r\n"))) != NULL)
     { 
       gtk_list_store_append (GTK_LIST_STORE (list_rooms), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_rooms), 
	                    &iter,
                            0, msg,
	                    -1);
			printf("msg is %s\n",msg);
			//g_free (msg);
     }
	
}
void create_room() {
	// Try first to add user in case it does not exist.
	char response[ MAX_RESPONSE ];
	nr++;
	cs++;
	sendCommand(host, port, "CREATE-ROOM", user, password, args, response);
	char *rooms = strdup(args);
	printf("rooms is %s\n",rooms);
	if (!strcmp(response,"OK\r\n")) {
		printf("Room %s added\n", args);
	}
gtk_list_store_clear(GTK_LIST_STORE(list_rooms));
update_list_rooms();

}
void update_list_messages(){
gtk_list_store_clear(GTK_LIST_STORE(list_messages));
	GtkTreeIter iter;
    int i;
	

	//list_room();
	char response[ MAX_RESPONSE ];
	char * temp = (char *)malloc(80*sizeof(char));
   strcpy(temp,"0");
	int x = 0;
	//temp = sprintf("%d %s",x,tep);
	strcat(temp," ");
	strcat(temp,tep);
	//sprintf(temp,"");
	printf("temp is %s\n",temp);
	sendCommand(host, port, "GET-MESSAGES", user, password, temp, response);
	if(!strcmp(response," "))
 	{
		return;
	}
	printf("Response is %s\n",response);
	gchar *msg = g_strdup_printf(strtok(response,"\r\n"));
	printf("msg is %s length is %d\n",msg,strlen(msg));
	gtk_list_store_append (GTK_LIST_STORE (list_messages), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_messages), 
	                    &iter,
                            0, msg,
	                    -1);
	
	while((msg = g_strdup_printf(strtok(NULL,"\r\n"))) != NULL)
     { 
		

       gtk_list_store_append (GTK_LIST_STORE (list_messages), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_messages), 
	                    &iter,
                            0, msg,
	                    -1);
			printf("msg is %s\n",msg);
			//g_free (msg);
  
}

}
void update_list_user(){
GtkTreeIter iter;
    int i;
	

	//list_room();
	char response[ MAX_RESPONSE ];
	sendCommand(host, port, "GET-USERS-IN-ROOM", user, password, args, response);
	if(!strcmp(response," "))
 	{
		return;	
	}
	printf("Response is %s\n",response);
	gchar *msg = g_strdup_printf(strtok(response,"\r\n"));
	printf("msg is %s\n",msg);
	gtk_list_store_append (GTK_LIST_STORE (list_user), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_user), 
	                    &iter,
                            0, msg,
	                    -1);
	
	while((msg = g_strdup_printf(strtok(NULL,"\r\n"))) != NULL)
     { 
       gtk_list_store_append (GTK_LIST_STORE (list_user), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_user), 
	                    &iter,
                            0, msg,
	                    -1);
			printf("msg is %s\n",msg);
			//g_free (msg);
    }

}
static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text; //works on pressing enter
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
	const gchar *ent;
	ent = strdup(gtk_entry_get_text (GTK_ENTRY (rooms))); 
	args = strdup(gtk_entry_get_text (GTK_ENTRY (rooms)));
	send_message(entry_text);	
	update_list_messages();	
}

static void entry_toggle_visibility( GtkWidget *checkbutton,
                                     GtkWidget *entry )
{
  gtk_entry_set_visibility (GTK_ENTRY (entry),
			    GTK_TOGGLE_BUTTON (checkbutton)->active);
}
/* Create the list of "messages" */
static GtkWidget *create_list( const char * titleColumn, GtkListStore *model )
{
    GtkWidget *scrolled_window;
    //GtkWidget *tree_view;
    //GtkListStore *model;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;

    int i;
   
    /* Create a new scrolled window, with scrollbars only if needed */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
				    GTK_POLICY_AUTOMATIC, 
				    GTK_POLICY_AUTOMATIC);
   
    //model = gtk_list_store_new (1, G_TYPE_STRING);
    tree_view = gtk_tree_view_new ();
    gtk_container_add (GTK_CONTAINER (scrolled_window), tree_view);
    gtk_tree_view_set_model (GTK_TREE_VIEW (tree_view), GTK_TREE_MODEL (model));
    gtk_widget_show (tree_view);
   
    cell = gtk_cell_renderer_text_new ();

    column = gtk_tree_view_column_new_with_attributes (titleColumn,
                                                       cell,
                                                       "text", 0,
                                                       NULL);
  
    gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view),
	  		         GTK_TREE_VIEW_COLUMN (column));

    return scrolled_window;
}
   char * mystrtrim(char * s) {
	char * s1= (char *)malloc(30*sizeof(char));
	char *t1 = s1; 
	char * t = s;
	while(*t != '\0')
	{
		//	printf("%c\n",*s);
		if(*t != ' ')
		{
			//printf("%c\n",*s );
			*t1 = *t;
			//s++;
			//	printf("%c \n",*s1);
			t1++;
		}
		t++;
	}
	//*s1 = '\0';
	// printf("s %s\n",s);
	//	s = s1;
	//	printf("s1 %s\n",s1);
	strcpy(s1,s);
	return s;
}
/* Add some text to our text widget - this is a callback that is invoked
when our window is realized. We could also force our window to be
realized with gtk_widget_realize, but it would have to be part of
a hierarchy first */

static void insert_text( GtkTextBuffer *buffer, const char * initialText )
{
   GtkTextIter iter;
 
   gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
   gtk_text_buffer_insert (buffer, &iter, initialText,-1);
}
   
/* Create a scrolled text area that displays a "message" */
static GtkWidget *create_text( const char * initialText )
{
   GtkWidget *scrolled_window;
   GtkWidget *view;
   GtkTextBuffer *buffer;

   view = gtk_text_view_new ();
   buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

   scrolled_window = gtk_scrolled_window_new (NULL, NULL);
   gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
		   	           GTK_POLICY_AUTOMATIC,
				   GTK_POLICY_AUTOMATIC);

   gtk_container_add (GTK_CONTAINER (scrolled_window), view);
   insert_text (buffer, initialText);

   gtk_widget_show_all (scrolled_window);

   return scrolled_window;
}
void enter_room(char * s)
{
printf("s is %s\n", s);
char response[ MAX_RESPONSE ];
char * try = (char *)malloc(80* sizeof(char));;
args=strdup(s);
args = mystrtrim(args);
printf("args is %shjud\n",args);
sendCommand(host, port, "ENTER-ROOM", user, password, args, response);
if (!strcmp(response,"OK\r\n")) {
		printf("user %s entered\n", user);
		sprintf(try,"%s has entered",user);
		if(try!=NULL)
		{
			send_message(try);
		}
	}
gtk_list_store_clear(GTK_LIST_STORE(list_user));
update_list_user();
}

leave_room()
{
	
char response[ MAX_RESPONSE ];
char * try = (char *)malloc(80 * sizeof(char));
args = mystrtrim(args);
printf("args is %shjud\n",args);
sprintf(try,"%s has left",user);
		if(try!=NULL)
		{
			send_message(try);
		}
sendCommand(host, port, "LEAVE-ROOM", user, password, args, response);
printf("response is %s\n",response);
if (!strcmp(response,"OK\r\n")) {
		printf("user %s left\n", user);
		//printf("user %s entered\n", user);
		
	
printf("turd\n");
gtk_list_store_clear(GTK_LIST_STORE(list_user));
update_list_user();
}
}




static void on_changed( GtkWidget *widget, GtkWidget *widget1)
{
   printf("Hello World\n");

	GtkTreeIter iter;
 GtkTreeModel *model;
char *value;
		//selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list_rooms));
 //text = (char*)malloc(50 * sizeof(char));
if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter)) {
printf("5\n");
    gtk_tree_model_get(model, &iter, 0, &value,  -1);
	tep = strdup(value);
	enter_room(value);

}
}
static gboolean
time_handler(GtkWidget *widget)
{
printf("3\n");
printf("cs is %d\n",cs);
if(au>=1)
{
gtk_list_store_clear(GTK_LIST_STORE(list_rooms));
update_list_rooms();

}
if(cs>=1)
{
gtk_list_store_clear(GTK_LIST_STORE(list_user));
update_list_user();
}
if(mm>=1)
{
gtk_list_store_clear(GTK_LIST_STORE(list_messages));
update_list_messages();
}
//update_list_user();
printf("30\n");
}



int main( int   argc,
          char *argv[])
{

    //GtkWidget *list;
    //GtkWidget *messages;
    //GtkWidget *myMessage;
	//GtkWidget *userlist;
	//GtkWidget *ulist;
	//GtkWidget *username;
	//GtkWidget *password;
	//GtkWidget *rooms;
	GdkColor color;
	gdk_color_parse("#FFCCCC",&color);
    gtk_init (&argc, &argv);
   
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Paned Windows");
    g_signal_connect (window, "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (GTK_WIDGET (window), 450, 400);

    // Create a table to place the widgets. Use a 7x4 Grid (7 rows x 4 columns)
    GtkWidget *table = gtk_table_new (10, 10, TRUE);//7,4
    gtk_container_add (GTK_CONTAINER (window), table);
    gtk_table_set_row_spacings(GTK_TABLE (table), 10);//5
    gtk_table_set_col_spacings(GTK_TABLE (table), 10);//5
	gtk_widget_modify_bg(window,GTK_STATE_NORMAL,&color);
    
	gtk_widget_show (table);

    // Add list of rooms. Use columns 0 to 4 (exclusive) and rows 0 to 4 (exclusive)
    list_rooms = gtk_list_store_new (1, G_TYPE_STRING);
    //update_list_rooms();
    list = create_list ("Rooms", list_rooms);
    gtk_table_attach_defaults (GTK_TABLE (table), list, 8, 10, 0, 3);//2,4,0,2
		selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view)); 	  
	g_signal_connect(tree_view, "row-activated", 
     G_CALLBACK(on_changed), selection);
	//selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list_rooms));
	 //g_signal_connect(selection, "changed", 
      //G_CALLBACK(on_changed), NULL); 	
     gtk_widget_show (list);
   
    // Add messages text. Use columns 0 to 4 (exclusive) and rows 4 to 7 (exclusive) 
	list_messages = gtk_list_store_new (1, G_TYPE_STRING);
	mlist = create_list("SERVER MESSAGES",list_messages);
    //messages = create_text ("SERVER MESSAGES\n");
    gtk_table_attach_defaults (GTK_TABLE (table), mlist, 4, 8, 0, 7);//0,4,2,5
	gtk_widget_show (mlist);
    // Add messages text. Use columns 0 to 4 (exclusive) and rows 4 to 7 (exclusive) 
	//userlist = create_text ("USERS will come here\n");
	//gtk_table_attach_defaults (GTK_TABLE (table), userlist, 8, 10, 7, 10);
	//gtk_widget_show (userlist);
    list_user = gtk_list_store_new (1, G_TYPE_STRING);
    //update_list_user();
    ulist = create_list ("Users", list_user);
    gtk_table_attach_defaults (GTK_TABLE (table), ulist, 8, 10, 3, 6);//2,4,0,2
    gtk_widget_show (ulist);
	//char *text;
	//selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list_rooms));
	// g_signal_connect(selection, "changed", 
     // G_CALLBACK(on_changed), text);


    myMessage = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY (myMessage), "ENTER MESSAGE");
    //myMessage = create_text ("Sending message....\n");
	gtk_entry_set_max_length(GTK_ENTRY (myMessage), 300);    
	gtk_table_attach_defaults (GTK_TABLE (table), myMessage, 4, 8, 7, 9);//0,4,5,7
	  //  g_signal_connect (myMessage, "activate",
		//      G_CALLBACK (enter_callback),
		  //    myMessage);
    gtk_widget_show (myMessage);

    // Add send button. Use columns 0 to 1 (exclusive) and rows 4 to 7 (exclusive)
    GtkWidget *send_button = gtk_button_new_with_label ("Send");
    gtk_table_attach_defaults(GTK_TABLE (table), send_button, 8, 10, 9, 10); //0,1,7,8
	    g_signal_connect (send_button, "clicked",
		      G_CALLBACK (enter_callback), myMessage);
	gtk_widget_show (send_button);
    
    username = gtk_entry_new();
	gtk_entry_set_text (GTK_ENTRY (username), "USERNAME");
	gtk_entry_set_max_length (GTK_ENTRY (username), 40);
    gtk_table_attach_defaults (GTK_TABLE (table), username, 0, 4, 0, 1);//0,4,5,7
    gtk_widget_show (username);	
    //array[0] = username; //added	
	
	 //GtkWidget *check = gtk_check_button_new_with_label ("Viewable");
	 //gtk_table_attach_defaults (GTK_TABLE (table), check, 0, 2, 4, 5);//0,4,5,7
    //gtk_widget_show (check);	 		
    
	pass = gtk_entry_new();
	gtk_entry_set_text (GTK_ENTRY (pass), "Password");
	//gtk_entry_set_text(pass,"Password");
     //pass = create_text ("Password");
     //g_signal_connect (check, "toggled",
	   //           G_CALLBACK (entry_toggle_visibility), pass);
    //gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    
	gtk_entry_set_max_length (GTK_ENTRY (pass), 50);
    gtk_table_attach_defaults (GTK_TABLE (table), pass, 0, 4, 1, 2);//0,4,5,7
	gtk_entry_set_visibility(GTK_ENTRY(pass),FALSE);
    gtk_widget_show (pass);	
	//array[1] = pass; //added
	
	//rooms = create_text("Room Name\n");	
	rooms = gtk_entry_new();
	gtk_entry_set_text (GTK_ENTRY (rooms), "Enter Room Name");	 
	gtk_table_attach_defaults (GTK_TABLE (table), rooms, 0, 4, 8, 9);//0,4,5,7
    gtk_widget_show (rooms);		
	
	GtkWidget *create_button = gtk_button_new_with_label ("Create Room");
    gtk_table_attach_defaults(GTK_TABLE (table), create_button, 0, 4, 9, 10); //0,1,7,8
    gtk_widget_show (create_button);
	g_signal_connect (create_button, "clicked",
		      G_CALLBACK (hello1), rooms);	
	

	 // GtkWidget *label = gtk_label_new("");
	//char * test1;
	//selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));
	//  g_signal_connect(tree_view, "row-activated", 
      //G_CALLBACK(update_list_rooms), NULL);
	

	GtkWidget *signin_button = gtk_button_new_with_label ("SignIn");
    gtk_table_attach_defaults(GTK_TABLE (table), signin_button, 0, 4, 2, 3); //0,1,7,8
    gtk_widget_show (signin_button);
	g_signal_connect (signin_button, "clicked",
		      G_CALLBACK (hello), username);	

    GtkWidget *signup_button = gtk_button_new_with_label ("SignUp");
    gtk_table_attach_defaults(GTK_TABLE (table), signup_button, 0, 4, 3, 4); //0,1,7,8
    gtk_widget_show (signup_button);	
    g_signal_connect (signup_button, "clicked",
		      G_CALLBACK (hello), username);

	GtkWidget *leave_button = gtk_button_new_with_label ("Leave room");
    gtk_table_attach_defaults(GTK_TABLE (table), leave_button, 0, 4, 4, 5); //0,1,7,8
g_signal_connect (leave_button, "clicked",
		      G_CALLBACK (hello2), rooms);    
gtk_widget_show (leave_button);
		
	GtkWidget *list_button = gtk_button_new_with_label ("LIST ROOM");
    gtk_table_attach_defaults(GTK_TABLE (table), list_button, 0, 4, 5, 6); //0,1,7,8
g_signal_connect (list_button, "clicked",
		      G_CALLBACK (hello3), NULL);    
gtk_widget_show (list_button);
		
	/*GtkWidget *list_button = gtk_button_new_with_label ("List Rooms");
    gtk_table_attach_defaults(GTK_TABLE (table), list_button, 0, 4, 3, 4); //0,1,7,8
    gtk_widget_show (list_button);	
	//g_signal_connect (list_button, "clicked",
		//      G_CALLBACK (update_list_rooms), NULL);*/
	host = "localhost";
    port = 2016; 

	g_timeout_add(5000, (GSourceFunc) time_handler, (gpointer) window);
   time_handler(window);
    gtk_widget_show (table);
    gtk_widget_show (window);
    gtk_main ();

    return 0;
}

