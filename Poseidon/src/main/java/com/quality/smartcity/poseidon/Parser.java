/**
 * Created by Axel ROLLO on 24/11/2017.
 */
package com.quality.smartcity.poseidon;

import android.os.AsyncTask;
import android.util.ArrayMap;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

class Parser {

    private static Map<String, String> dataList = new ArrayMap<>();
    private static Communication getJSON;

    /**
     * Launch the communication to catch JSON file.
     *
     * @param urlWebService The raspberrian web service to access database.
     */
    static void launchJSON(final String urlWebService){

        if(getJSON != null && getJSON.getStatus() == AsyncTask.Status.RUNNING){
            getJSON.cancel(true);
            Log.i("Parser", "[launchJSON] Status of the com on cancel: "+getJSON.getStatus());
        }
        getJSON = new Communication();

        Log.i("Parser", "[launchJSON] Status of the com : "+getJSON.getStatus());
        getJSON.setUrlWebService(urlWebService);
        getJSON.execute();

        Log.i("Parser", "[launchJSON] Status of the com after execute : "+getJSON.getStatus());
    }

    /**
     * Launch the communication to get a table JSON file.
     *
     * @param table The table name to find.
     */
    static List<String> launchGetTableJSON(final String table){
        try {
            if(table != null && getDataList() != null && getJSON.getJsonData() != null){
                return parseOneTable(getJSON.getJsonData(), table);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return null;
    }

    /**
     * Launch the communication to get a table JSON file.
     *
     * @param table The table name to find.
     */
    static List<String> launchGetTableDateJSON(final String table){
        try {
            if(table != null && getDataList() != null && getJSON.getJsonData() != null){
                return parseOneTableForDate(getJSON.getJsonData(), table);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return null;
    }


    /**
     * Parse a JSON file into an array map of data.
     *
     * @param json The JSON file to convert.
     * @throws JSONException JSON Exception to avoid JSON convertions.
     */
    static void parseJSON(String json) throws JSONException {
        JSONArray jsonArrayGeneral = new JSONArray(json);

        for (int i = 0; i < jsonArrayGeneral.length() - 1; i++) {
            JSONArray data = jsonArrayGeneral.getJSONArray(i);

            String data_name = data.getJSONObject(0).getString("table_name");
            JSONArray jsonArrayTable = (JSONArray) jsonArrayGeneral.get(i);

            for (int j = 1; j < jsonArrayTable.length(); j++) {
                JSONObject jsonObject = data.getJSONObject(j);
                String valeur = jsonObject.get("valeur").toString();

                /** Capped UV data*/
                if("UV".compareTo(data_name) == 0 && Integer.parseInt(valeur) > 11){
                    valeur = "11";
                }
                addData(data_name, valeur);
            }
        }

    }

    /**
     * Parse one table of a JSON file into a list of data.
     *
     * @param json The json file.
     * @param tableName The json table name to parse.
     * @return A list of data from the table.
     * @throws JSONException JSON Exception to avoid JSON convertions.
     */
    private static List<String> parseOneTable(String json, String tableName) throws JSONException{
        JSONArray jsonArrayGeneral = new JSONArray(json);
        JSONArray jsonArrayTable;
        List<String> tableList = new ArrayList<>();

        for(int i=0; i<jsonArrayGeneral.length()-1;i++) {
            JSONArray data = jsonArrayGeneral.getJSONArray(i);
            if (data.getJSONObject(0).getString("table_name").equals(tableName)) {
                jsonArrayTable = (JSONArray) jsonArrayGeneral.get(i);
                Log.i("parseOneTable", data.getJSONObject(0).getString("table_name") + " successfully found !");

                for(int j=1; j<jsonArrayTable.length(); j++) {
                    JSONObject jsonArrayValue = jsonArrayTable.getJSONObject(j);
                    String value = jsonArrayValue.getString("valeur");
                    Log.i("parseOneTable", "jsonArrayValue : " + jsonArrayValue);
                    //Log.i("parseOneTable", "value : " + value);
                    tableList.add(value);
                }
                return tableList;
            }
        }
        return null;
    }

    /**
     * Parse one table for date of a JSON file into a list of data.
     *
     * @param json The json file.
     * @param tableName The json table date to parse.
     * @return A list of data date from the table.
     * @throws JSONException JSON Exception to avoid JSON convertions.
     */
    static List<String> parseOneTableForDate(String json, String tableName) throws JSONException{
        JSONArray jsonArrayGeneral = new JSONArray(json);
        JSONArray jsonArrayTable;
        List<String> tableDateList = new ArrayList<>();

        for(int i=0; i<jsonArrayGeneral.length()-1;i++) {
            JSONArray data = jsonArrayGeneral.getJSONArray(i);
            if (data.getJSONObject(0).getString("table_name").equals(tableName)) {
                jsonArrayTable = (JSONArray) jsonArrayGeneral.get(i);
                Log.i("parseOneTable", data.getJSONObject(0).getString("table_name") + " successfully found !");

                for (int j = 1; j < jsonArrayTable.length(); j++) {
                    JSONObject jsonArrayValue = jsonArrayTable.getJSONObject(j);
                    String value = jsonArrayValue.getString("valeur");
                    String date = jsonArrayValue.getString("date");
                    //Log.i("parseOneTable", "value : " + value);
                    tableDateList.add(date);
                }
                Log.i("parseOneTable", "jsonArray list date : " + tableDateList);
                return tableDateList;
            }
        }
        return null;
    }

    /**
     * Add a data on the array map.
     *
     * @param name The name of the data.
     * @param value The value of the data.
     */
    private static void addData(String name, String value){
        dataList.put(name,value);
    }

    /**
     * Getter to get a data list.
     *
     * @return The data list.
     */
    private static Map<String, String> getDataList(){
        return dataList;
    }

    /**
     * Getter to get a specific element from the data list.
     *
     * @param name The key of the name.
     * @return The data concerned.
     */
    static int getElementOnDataList(String name){
        if(dataList.get(name)!=null){
            return Integer.parseInt(dataList.get(name));
        }else {
            return 0;
        }
    }

}
