package it.unipr.template;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class ServerThread implements Runnable
{
    private Server server;
    private Socket socket;

    public ServerThread(final Server server, final Socket socket)
    {
        this.server = server;
        this.socket = socket;
    }

    public void run()
    {
        ObjectInputStream is = null;
        ObjectOutputStream os = null;

        try
        {
            is = new ObjectInputStream(new BufferedInputStream(this.socket.getInputStream()));
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return;
        }

        while (true)
        {
            try
            {
                if (os == null)
                {
                    os = new ObjectOutputStream(new BufferedOutputStream(this.socket.getOutputStream()));
                }
                
                // TODO: send message to the connected client.
                /*
                Message message = new Message();

                os.writeObject(message);
                os.flush();
                */

                Object object = is.readObject();

                // TODO: use thee received object.
                /*
                if (object instanceof Class)
                {
                    Class receivedMessage = (Class) object;

                    // Do some stuff...
                    // ... and send a message to the server.

                    os.writeObject(response);
                    os.flush();
                }
                */

                if (this.server.getPool().getActiveCount() == 1)
                {
                    this.server.close();
                }

                this.socket.close();
                break;
            }
            catch (Exception e)
            {
                e.printStackTrace();
                System.exit(-1);
            }
        }
    }
}
