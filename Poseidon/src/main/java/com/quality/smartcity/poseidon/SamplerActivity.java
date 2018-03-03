package com.quality.smartcity.poseidon;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static com.quality.smartcity.poseidon.Parser.launchGetTableDateJSON;
import static com.quality.smartcity.poseidon.Parser.launchGetTableJSON;
import static com.quality.smartcity.poseidon.Parser.launchJSON;
import static com.quality.smartcity.poseidon.Parser.parseOneTableForDate;

public class SamplerActivity extends AppCompatActivity {

    private SwipeRefreshLayout mSwipeRefreshLayout;
    private CustomAdapter adapter;
    private TextView releve_date;
    private Sampler sampler;
    private List<Data> myDataList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sampler2);

        sampler = Sampler.getInstance();
        myDataList = sampler.getDataList();

        ListView dataList = (ListView) findViewById(R.id.myList);
        releve_date = (TextView) findViewById(R.id.releve_date);

        giveDateForSample();

        final List<Map<String, String>> list = new ArrayList<>();

        Map<String, String> map;

        /**
         * Fill text thanks to a list of data. The text is refresh following the example below :
         * "<>value of the data</> <>unit of the data</>"
         */
        for(Data d: myDataList){
            map = new HashMap<>();
            map.put("Data title",d.getName());
            map.put("Data",String.valueOf(d.getCurrentValue())+" "+d.getUnit());

            list.add(map);
        }

        adapter = new CustomAdapter(this,
                list, R.layout.element , new String[]{"Data title", "Data"}, new int[]{R.id.data_title, R.id.data});
        dataList.setAdapter(adapter);

        mSwipeRefreshLayout = (SwipeRefreshLayout) findViewById(R.id.swiperefresh);

        mSwipeRefreshLayout.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {

            @Override
            public void onRefresh() {
                Intent intent = new Intent(SamplerActivity.this, SamplerActivity.class);
                intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                startActivity(intent);
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        launchJSON(getResources().getString(R.string.url));
    }

    /**
     * Set a date and an hour for each sample.
     */
    void giveDateForSample(){
        Date date = new Date();
        releve_date.setText("Relevé du "+date.toLocaleString());
    }

    /**
     * Generate a dialog information for a data.
     *
     * @param data The data associated with the dialog box.
     */
    public static void generateDialogInfo(final Data data, TextView tv, final Context context){
        AlertDialog.Builder ad = new AlertDialog.Builder(context);
        ad.setMessage("Données actuelles");
        ad.setTitle("Relevé "+data.getName());
        ad.setMessage("Données actuelles: "+tv.getText()+"\nStatut critique : "+data.getCriticValue()
                +" "+data.getUnit()+"\nStatut dangereux : "+data.getDangerousValue()+" "+data.getUnit());
        ad.setPositiveButton("close", new DialogInterface.OnClickListener(){
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.cancel();
            }
        }).setCancelable(true);
        ad.setNegativeButton("Voir Graphique", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                Log.i("php table to found", data.getName().toUpperCase());
                List<Number> dataList = convertStringListIntoIntegerList(launchGetTableJSON(data.getName().toUpperCase()));
                List<Number> emptyDataList = new ArrayList<>();
                List<String> dateList = launchGetTableDateJSON(data.getName().toUpperCase());
                Log.i("generateDialogInfo", "date list = " + dateList);
                emptyDataList.add(0);
                Intent intent = new Intent(context, SimpleXYPlotActivity.class);
                if(dataList != null)
                    intent.putStringArrayListExtra("dataList", (ArrayList) dataList);
                else intent.putStringArrayListExtra("dataList", (ArrayList) emptyDataList);
                if(dateList!= null){
                    intent.putStringArrayListExtra("date", (ArrayList) dateList);
                }else intent.putStringArrayListExtra("date", (ArrayList) emptyDataList);
                context.startActivity(intent);

            }
        });
        ad.show();
    }

    public static List<Number> convertStringListIntoIntegerList(List<String> myList){
        List<Number> list = new ArrayList<>();
        if(myList != null) {
            for (String element : myList) {
                list.add(Integer.valueOf(element));
            }
            return list;
        }
        return null;
    }

}
