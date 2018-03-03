/**
 * Created by Axel ROLLO on 06/11/2017.
 */
package com.quality.smartcity.poseidon;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

import com.jjoe64.graphview.DefaultLabelFormatter;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.DataPointInterface;
import com.jjoe64.graphview.series.LineGraphSeries;
import com.jjoe64.graphview.series.OnDataPointTapListener;
import com.jjoe64.graphview.series.Series;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

/**
 * A class to manage graph.
 */
public class SimpleXYPlotActivity extends AppCompatActivity {

    private static final Number DEFAULT_NUMBER = 0;
    private static List<Number> numberList;
    private static List<String> dateList;
    private SimpleDateFormat sdfClock;
    private static Date myDate;
    private static long scaleMaxX;
    private static long scaleMinX;
    private static int scaleMaxY;
    private static int scaleMinY;


    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.simple_xy_plot_example);

        /** Getting bundle. */
        Bundle bundle = getIntent().getExtras();
        numberList = (List<Number>) bundle.get("dataList");
        dateList = (List<String>) bundle.get("date");

        /** Setting the date format. */
        sdfClock = new SimpleDateFormat("hh:mm:ss");

        if(numberList.size() == 1 && numberList.get(0)== DEFAULT_NUMBER){
            /** Nothing to do. */
            Log.e("SimpleXY", "No data to display");
        }else{
            String[] dateInfo = extractHours(dateList);
            Log.i("SimpleXY", "starting date =  "+dateInfo);
            DataPoint dp[] = generateData(numberList.size());

            GraphView graph = (GraphView) findViewById(R.id.graph);
            LineGraphSeries<DataPoint> series = new LineGraphSeries<>(dp);

            series.setOnDataPointTapListener(new OnDataPointTapListener() {
                @Override
                public void onTap(Series series, DataPointInterface dataPoint) {
                    Toast.makeText(getApplicationContext(), "Donnée : "+ dataPoint.getY()
                            + " Clock : "+sdfClock.format((long)dataPoint.getX()),
                            Toast.LENGTH_SHORT).show();
                }
            });

            /** delimit the graph viewport and scalable access. */
            graph.getViewport().setScrollable(true);
            graph.getViewport().setScalable(true);
            graph.getViewport().setScalableY(true);

            graph.getViewport().setXAxisBoundsManual(true);
            graph.getViewport().setMinX(scaleMinX);
            graph.getViewport().setMaxX(scaleMaxX);

            graph.getViewport().setMinY(scaleMinY);
            graph.getViewport().setMaxY(scaleMaxY);

            /** configuration of ontap element. */
            graph.getGridLabelRenderer().setLabelFormatter(new DefaultLabelFormatter() {
                @Override
                public String formatLabel(double value, boolean isValueX) {
                    if(isValueX){
                        return sdfClock.format(new Date((long) value));
                    }else{
                        return super.formatLabel(value,false);
                    }
                }
            });
            graph.getGridLabelRenderer().setNumHorizontalLabels(3);

            graph.addSeries(series);
        }
    }

    /**
     * Generate data points for the graph.
     *
     * @param size The nomber of data to add.
     * @return A tab of DataPoint representing data.
     */
    private DataPoint[] generateData(int size) {
        DataPoint[] values = new DataPoint[size];
        Calendar c = Calendar.getInstance();
        c.setTime(myDate);
        scaleMaxX = c.getTimeInMillis();
        scaleMinX = c.getTimeInMillis();
        scaleMaxY = (Integer) numberList.get(0);
        scaleMinY = (Integer) numberList.get(0);

        for (int i = 0; i < size; i++) {
            DataPoint v = new DataPoint(c.getTime(), (Integer) numberList.get(i));
            values[i] = v;
            c.add(Calendar.MINUTE, 15);

            if(c.getTimeInMillis() > scaleMaxX){
                scaleMaxX = c.getTimeInMillis();
            }
            if((Integer) numberList.get(i) > scaleMaxY){
                scaleMaxY = (Integer) numberList.get(i);
            }
            if((Integer) numberList.get(i) < scaleMinY){
                scaleMinY = (Integer) numberList.get(i);
            }
            //Log.i("Date", "date "+ i+" = "+c.toString());
        }
        return values;
    }

    /**
     * Extract the date from the first releve. Add 15 minutes for each new point.
     *
     * @param list The list of data.
     * @return A tab of String representing hours, minutes and secondes.
     */
    private String[] extractHours(List<String> list){
        String full_date[];
        String date[];
        String year;
        String month;
        String day;

        String firstElem = list.get(0);
        full_date = firstElem.split(" ");
        date = full_date[0].split("-");
        year = date[0];
        month = date[1];
        day = date[2];

        String clock[] = full_date[1].split(":");
        Integer hours = Integer.valueOf(clock[0]);
        Integer min = Integer.valueOf(clock[1]);
        Integer sec = Integer.valueOf(clock[2]);

        try {
            myDate = sdfClock.parse(full_date[1]);
            Log.i("SimpleXY", "parse : "+myDate +" Hours : "+myDate.getTime());
        } catch (ParseException e) {
            e.printStackTrace();
        }

        return new String[]{year, month, day};
    }
}
