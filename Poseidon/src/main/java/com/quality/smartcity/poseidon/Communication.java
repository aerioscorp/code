/**
 * Created by Axel ROLLO on 23/11/2017.
 */
package com.quality.smartcity.poseidon;

import android.os.AsyncTask;
import android.util.Log;

import org.json.JSONException;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

class Communication extends AsyncTask<Void, Void, String>{

    private String urlWebService;
    private String jsonData;

    public Communication(){}

    /**
     * Set the url for the web service.
     *
     * @param url The url.
     */
    void setUrlWebService(final String url){
        this.urlWebService = url;
    }

    /**
     * This method will be called before execution
     * The network operation may take some time
     */
    @Override
    protected void onPreExecute() {
        super.onPreExecute();
    }

    /**
     * This method will be called after execution
     *
     * @param s the String of the database.
     */
    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);
        if(s != null) {
            Log.i("DBB ", s);
        }
        try{
            if(s != null)
                Parser.parseJSON(s);
        }catch(JSONException e) {
            e.printStackTrace();
        }

    }

    /**
     * Background communication task.
     *
     * @param voids A void.
     * @return JSON data.
     */
    @Override
    protected String doInBackground(Void... voids) {
        try {
            /** creating a URL */
            URL url = new URL(urlWebService);

            /** Opening the URL using HttpURLConnection*/
            HttpURLConnection con = (HttpURLConnection) url.openConnection();

            /** StringBuilder object to read the string from the service*/
            StringBuilder sb = new StringBuilder();

            /** We will use a buffered reader to read the string from service*/
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(con.getInputStream()));

             /** A simple string to read values from each line*/
            String json;

             /** reading until we don't find null*/
            while ((json = bufferedReader.readLine()) != null) {
                sb.append(json + "\n");
            }
            jsonData = sb.toString().trim();
            return jsonData;
        } catch (Exception e) {
            return null;
        }

    }

    public String getJsonData(){
        return jsonData;
    }

}