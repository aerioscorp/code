/**
 * Created by Axel ROLLO on 30/11/2017.
 */
package com.quality.smartcity.poseidon;

import android.content.Context;
import android.graphics.Color;
import android.view.View;
import android.view.ViewGroup;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import java.util.List;
import java.util.Map;

public class CustomAdapter extends SimpleAdapter {

    private Data myData;
    private static TextView nameText;
    private static TextView dataText;
    private Sampler mySampler;

    /**
     * Constructor
     *
     * @param context  The context where the View associated with this SimpleAdapter is running
     * @param data     A List of Maps. Each entry in the List corresponds to one row in the list. The
     *                 Maps contain the data for each row, and should include all the entries specified in
     *                 "from"
     * @param resource Resource identifier of a view layout that defines the views for this list
     *                 item. The layout file should include at least those named views defined in "to"
     * @param from     A list of column names that will be added to the Map associated with each
     *                 item.
     * @param to       The views that should display column in the "from" parameter. These should all be
     *                 TextViews. The first N views in this list are given the values of the first N columns
     */
    public CustomAdapter(Context context, List<? extends Map<String, ?>> data, int resource, String[] from, int[] to) {
        super(context, data, resource, from, to);
    }

    /**
     * @param position
     * @param convertView
     * @param parent
     * @return
     */
    @Override
    public View getView(int position, View convertView, final ViewGroup parent) {
        View view = super.getView(position, convertView, parent);
        mySampler = Sampler.getInstance();

        nameText = (TextView) view.findViewById(R.id.data_title);
        dataText = (TextView) view.findViewById(R.id.data);

        List<Data> myList = mySampler.getDataList();
        final Data myData = Data.findDataAssociatedWithName(myList, nameText.getText());

        dataText.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                SamplerActivity.generateDialogInfo(myData, (TextView) v.findViewById(R.id.data), parent.getContext());
            }
        });

        if(myData.getCurrentValue() >= myData.getDangerousValue())
            dataText.setBackgroundColor(Color.RED);
        else if(myData.getCurrentValue() > myData.getCriticValue() && myData.getCurrentValue() < myData.getDangerousValue())
            dataText.setBackgroundColor(Color.YELLOW);
        else dataText.setBackgroundColor(Color.GREEN);

        //System.out.println("[CustomAdapter] "+nameText.getText() +" "+ dataText.getText());
        return view;
    }

    /**
     * @return
     */
    @Override
    public int getCount() {
        return super.getCount();
    }

    public static TextView getDataText(){
        return dataText;
    }
}
