/**
 * Created by Axel ROLLO on 26/10/2017.
 */
package com.quality.smartcity.poseidon;

import android.graphics.Color;
import android.widget.TextView;

import java.util.List;

class Data {

    private final int DEFAULT_CRITIC_VALUE = 200;
    private final int DEFAULT_DANGEROUS_VALUE = 300;
    private int id;
    private int criticValue;
    private int dangerousValue;
    private int currentValue;
    private String unit;
    private String name;

    /**
     * Data constructor using a value, an id, a textView and an unit.
     *
     * @param name The name of the data.
     * @param currentValue The current value of a sensor.
     * @param id The id of the data.
     * @param unit The unit of the data.
     */
    Data(String name, int currentValue, int id, String unit){
        new Data(name, currentValue, id, DEFAULT_CRITIC_VALUE, DEFAULT_DANGEROUS_VALUE, unit);
    }


    /**
     * The main Data constructor.
     *
     * @param name The name of the data.
     * @param currentValue The current value of a sensor.
     * @param id The id of the data.
     * @param criticValue The value considered critic. Give a starting fork of the value.
     * @param dangerousValue The value considered dangerous. Give a starting fork of the value.
     * @param unit The unit of the data.
     */
    Data(String name, int currentValue, int id, int criticValue, int dangerousValue, String unit){
        this.currentValue = currentValue;
        this.id = id;
        this.criticValue = criticValue;
        this.dangerousValue = dangerousValue;
        this.unit = unit;
        this.name = name;
    }

    /**
     * Evaluate the risk thanks to a data.
     * A dangerous data is corresponding to a priority "3".
     * A critic data is corresponding to a priority "2".
     * A normal/An average data is corresponding to a priority "1".
     *
     * @param data The data to analyse.
     */
    public static void evaluateDataRisk(Data data){
        /*if(data.getCurrentValue() >= data.getDangerousValue())
            setColorByRisk(data.getTextView(),3);
        else if(data.getCurrentValue() > data.getCriticValue() && data.getCurrentValue() <data.getDangerousValue())
            setColorByRisk(data.getTextView(),2);
        else setColorByRisk(data.getTextView(), 1);*/
    }

    /**
     * Attribute a color defined by the priority.
     * See also evaluateDataRisk.
     *
     * @param aTextView
     * @param priority
     */
    private static void setColorByRisk(TextView aTextView, int priority){
        if(priority == 1){
            aTextView.setBackgroundColor(Color.GREEN);
        }else if (priority == 2)
            aTextView.setBackgroundColor(Color.YELLOW);
        else if (priority == 3)
            aTextView.setBackgroundColor(Color.RED);
    }

    /**
     * Find a data on a list of Data according to his name.
     *
     * @param data The list of data.
     * @param name The name of the data to seek.
     * @return The Data object.
     */
    public static Data findDataAssociatedWithName(List<Data> data, CharSequence name){
        for(Data d: data){
            if(d.getName().compareTo((String)name) == 0){
                return d;
            }
        }
        System.out.println("[Data] No data found");
        return null;
    }

    /** Getters & Setters*/

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getCriticValue() {
        return criticValue;
    }

    public void setCriticValue(int criticValue) {
        this.criticValue = criticValue;
    }

    public int getDangerousValue() {
        return dangerousValue;
    }

    public void setDangerousValue(int dangerousValue) {
        this.dangerousValue = dangerousValue;
    }

    public String getUnit() {
        return unit;
    }

    public void setUnit(String unit) {
        this.unit = unit;
    }

    public int getCurrentValue() {
        return currentValue;
    }

    public void setCurrentValue(int currentValue) {
        this.currentValue = currentValue;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
