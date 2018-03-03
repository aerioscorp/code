/**
 * Created by Axel ROLLO on 30/11/2017.
 */
package com.quality.smartcity.poseidon;

import java.util.ArrayList;
import java.util.List;

import static com.quality.smartcity.poseidon.Parser.getElementOnDataList;

public class Sampler{

    private List<Data> myList;

    private static Sampler samplerInstance;

    private Sampler(){
        myList = new ArrayList<>();
        createData();
    }

    public static Sampler getInstance(){
        if(samplerInstance != null){
            return samplerInstance;
        }else {
            return new Sampler();
        }
    }

    /**
     * Create all data with good parameters.
     */
    private void createData() {
        /** Filling all the samplers. */
        Data co2 = new Data("co2", getElementOnDataList("CO2"), 1, 250, 400, "ppm");
        myList.add(co2);

        Data co = new Data("co", getElementOnDataList("CO"), 2, 199, 300, "ppm");
        myList.add(co);

        Data no2 = new Data("no2",  getElementOnDataList("NO2"), 3, 40, 200, "μg/m3");
        myList.add(no2);

        Data nh3 = new Data("nh3", getElementOnDataList("NH3"), 4, 5, 6, "mg/m3");
        myList.add(nh3);

        Data o3 = new Data("o3", getElementOnDataList("O3"), 5, 400, 500, "ppmm");
        myList.add(o3);

        Data uv = new Data("uv", getElementOnDataList("UV"), 6, 6, 8, "");
        myList.add(uv);

        Data lumi = new Data("luminosite", getElementOnDataList("LUMINOSITE"), 7, 25000, 35000, "ppmm");
        myList.add(lumi);

        Data temp = new Data("temperature", getElementOnDataList("TEMPERATURE"), 8, 30, 40, "°C");
        myList.add(temp);

        Data partic = new Data("particules", getElementOnDataList("PARTICULES"), 9, 2, 5, "mg/m3");
        myList.add(partic);

        Data press = new Data("pression", getElementOnDataList("PRESSION"), 10, 1500, 3000, "hPa");
        myList.add(press);

        Data humi = new Data("humidite", getElementOnDataList("HUMIDITE"), 11, 65, 90, "%");
        myList.add(humi);

        Data vent = new Data("vitesse_vent", getElementOnDataList("VITESSE_VENT"), 12, 70, 110, "m/s");
        myList.add(vent);

        Data pluv = new Data("pluviometrie", getElementOnDataList("PLUVIOMETRIE"), 13, 200, 305, "mm");
        myList.add(pluv);

        Data dirVent = new Data("direction du vent", 0, 14, 0, 0, "");
        myList.add(dirVent);
    }

    public List<Data> getDataList(){
        return myList;
    }
}
