## This is the protocol for communication between cumulusd (daemon) and cumulus (cloud)

So cumulusd is installed on the host computer and will now connect to the global cumulus server that is sitting on the cloud

The cumulus service on the cloud is expecting new connections from cumulusd (daemon) and will respond accordingly with some data parameters that will have some meaning for both of these parties. We will call it **commands**

Communication will happen over the SSL Sockets with TLS support.

We will now define some keywords for later use

1. **daemon_id** - It is the unique ID of the daemon installed on the host computer. On installation, this will be auto generated.
2. **user_id** - Upon installation of the daemon, user will need to login to cumulus (Google, Email, etc). After successful login, each user will have their own unique user_id.
3. **token** - Upon successful authentication, token will be saved and will be used to authorize with cumulus.
4. **content_port** - This is the port that is opened on the host computer, that is listening. cumulusd will route the incoming traffic to this port, and will also route the outgoing traffic from this port to cumulus.
5. **daemon_socket** - Upon successfull authentication and connection with the cumulus, the host computer will have a socket, created by cumulusd, that will be used to communicate and route traffic to-from cumulus.

*These protocols might change according to the need of the implementation. This is currently for guidance of the development process*

### Connect
This step will try to connect to the cumulus cloud service and make a socket connection, and send this initial command. The response will lead to success or terminate

`c daemon_id user_id token`

Response - 0 or 1

### Awake
This command will send awake signals to the cumulus, and will be used by cumulus for checking if a daemon is alive or not.

`awake`

Response - 0 or 1

### Data
This command will route the incoming data from **content_port** to the **daemon socket**

`data content_port_incoming_data`

Response - No response

### Close
This command will instruct the cumulus service to release the connection and release any allocated resources. Now no further communication will happen unless the daemon will re connect again upon user's intervention. Same thing will be taken care of by the cumulus service.

`close`

Response - No response