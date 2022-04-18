//package src;

import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;
import java.text.DecimalFormat;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;


class XMLGeneration {
    public static DecimalFormat df = new DecimalFormat("0.00");
    public static int count = 0;
    private static int call = 0;

    public static void main(String[] args) {

        System.out.println("Hello world");
        String userDirectory = Paths.get("")
                .toAbsolutePath()
                .toString();
        System.out.println(userDirectory);
        File inputFile = new File("vd012.xml");
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder;
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(inputFile);
            doc.getDocumentElement().normalize();

            NodeList nList = doc.getElementsByTagName("edge");
            System.out.println(nList.getLength());

            Document newDoc = dBuilder.newDocument();
            newDoc.appendChild(newDoc.createElement("routes"));
            Node root = newDoc.getDocumentElement();
            float M = 0;

            for (int i = 0; i < nList.getLength(); i++) {
                Node node = nList.item(i);
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) node;
                    String id = element.getAttribute("id");
                    if (id.charAt(0) == 'E') {
                        float x = Float.parseFloat(id.substring(1));
                        if (x > M)
                            M = x;
                    }

                }
            }
            
            System.out.println("\n" + (nList.getLength()/2));

            for (int i = 0; i < nList.getLength(); i++) {
                Node node = nList.item(i);
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) node;
                    String id = element.getAttribute("id");
                    double ran = Math.random();
                    if (id.charAt(0) == 'E' && id.charAt(1) != '0'
                    		&& ran <= 0.4
                    		) {
                        float x = Float.parseFloat(id.substring(1));
                        Node personFlow1 = CreatePersonFlow(newDoc, x, "a", M, i % 40);
                        Node personFlow2 = CreatePersonFlow(newDoc, x, "b", M, i % 40);
                        root.appendChild(personFlow1);
                        root.appendChild(personFlow2);
                    }

                }
            }
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transf;
            try {
                transf = transformerFactory.newTransformer();
                transf.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
                transf.setOutputProperty(OutputKeys.INDENT, "yes");
                transf.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
                DOMSource source = new DOMSource(newDoc);

                File myFile = new File("vd012.rou.xml");

                StreamResult console = new StreamResult(System.out);
                StreamResult file = new StreamResult(myFile);

                transf.transform(source, console);
                transf.transform(source, file);
            } catch (TransformerException e) {
                e.printStackTrace();
            }

        } catch (ParserConfigurationException | SAXException | IOException e) {
            e.printStackTrace();
        }

    }

    static Node CreatePersonFlow(Document doc, float x, String tail, float M, int begin) {
    	if(call % 30 == 0 && call > 0)
    		count++;
        Element personFlow = doc.createElement("personFlow");
        String id = "p" + Integer.toString((int) x) + tail;
        personFlow.setAttribute("id", id);
        personFlow.setAttribute("begin", "" + count);
        int beginRandom = (int) Math.floor(6*CustomerRandom.GetProbality());
        personFlow.setAttribute("period", "" + (5 + beginRandom));
        //personFlow.setAttribute("id", id);

        double pXa = (x < (M / 2 + 1)) ? (x * 1.0 / (M / 2 + 1)) : (x * 1.0 / M);
        Element walk = doc.createElement("walk");
        personFlow.appendChild(walk);
        if (tail == "a") {
            personFlow.setAttribute("impatience", df.format(pXa));
            walk.setAttribute("from", "E" + Integer.toString((int) x));
            walk.setAttribute("to", "-E" + Integer.toString((int) x));
        }
        if (tail == "b") {
            personFlow.setAttribute("impatience", df.format(1 - pXa));
            walk.setAttribute("to", "E" + Integer.toString((int) x));
            walk.setAttribute("from", "-E" + Integer.toString((int) x));
        }
        call++;
    	

        return personFlow;
    }
}