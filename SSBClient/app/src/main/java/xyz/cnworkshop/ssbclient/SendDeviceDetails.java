package xyz.cnworkshop.ssbclient;

import android.os.AsyncTask;
import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;

class SendDeviceDetails extends AsyncTask<String, Void, String> {

    @Override
    protected String doInBackground(String... urls) {
        // params comes from the execute() call: params[0] is the url.
        try {
            try {
                Log.e("SADDDDDD",urls[0]+urls[1]);
                return HttpPost(urls[0],urls[1]);
            } catch (JSONException e) {
                e.printStackTrace();
                Log.e("SADDDDDD","error");
                return "Error!";
            }
        } catch (IOException e) {
            Log.e("SADDDDDD","unable");
            return "Unable to retrieve web page. URL may be invalid.";
        }
    }
    private String HttpPost(String myUrl, String barCode) throws IOException, JSONException {
        String result = "";

        URL url = new URL(myUrl);

        // 1. create HttpURLConnection
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("POST");
        conn.setRequestProperty("Content-Type", "application/json; charset=utf-8");

        // 2. build JSON object
        JSONObject postData = new JSONObject();
        postData.put("barCode", barCode);

        // 3. add JSON content to POST request body
        setPostRequestContent(conn,postData);

        // 4. make POST request to the given URL
        conn.connect();

        // 5. return response message
        return conn.getResponseMessage()+"";

    }
    private void setPostRequestContent(HttpURLConnection conn,
                                       JSONObject jsonObject) throws IOException {
        OutputStream os = conn.getOutputStream();
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os, "UTF-8"));
        writer.write(jsonObject.toString());
        Log.i(MainActivity.class.toString(), jsonObject.toString());
        writer.flush();
        writer.close();
        os.close();
    }
    @Override
    protected void onPostExecute(String result) {
        super.onPostExecute(result);
        Log.e("TAG", result);
    }
}
