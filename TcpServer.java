import java.io.*;
import java.net.*;
import java.util.*;

public class TcpServer {
    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(5000);
            System.out.println("Server started… waiting for client…");

            Socket s = ss.accept();
            System.out.println("Client connected.");

            Scanner in = new Scanner(s.getInputStream());
            PrintWriter out = new PrintWriter(s.getOutputStream(), true);

            String fileName = in.nextLine();
            File file = new File(fileName);

            if (!file.exists()) {
                out.println("File not found!");
            } else {
                Scanner fileReader = new Scanner(file);
                while (fileReader.hasNextLine()) {
                    out.println(fileReader.nextLine());
                }
                fileReader.close();
            }

            s.close();
            ss.close();
            in.close();
            out.close();
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}

/*
 * Sample Output:
 * Server started… waiting for client…
 * Client connected.
 */