package it.unipr.template;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.ObjectInputStream;
import java.net.Socket;

public final class Client
{
    private static final int SPORT = 4444;
    private static final String SHOST = "localhost";

    public void run()
    {
        try
        {
            Socket client = new Socket(SHOST, SPORT);
            
            ObjectOutputStream os = new ObjectOutputStream(client.getOutputStream());
            ObjectInputStream is = null;

            while (true)
            {
                if (is == null)
                {
                    is = new ObjectInputStream(new BufferedInputStream(client.getInputStream()));
                }

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

                break;
            }

            System.out.println("Client closed.");
            client.close();
        }
        catch (IOException | ClassNotFoundException e)
        {
            e.printStackTrace();
        }
    }

    public static void main(final String[] args)
    {
        new Client().run();
    }
}
