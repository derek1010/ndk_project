package com.example.derek.csample1117;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    // Example of a call to a native method
    TextView tv = (TextView) findViewById(R.id.sample_text);
    tv.setText(stringFromJNI());


        final Button button = (Button) findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                // Perform action on click

                Log.d("derek", "call fork()");

                TextView tv = (TextView) findViewById(R.id.sample_text);
                tv.setText(fork());


            }
        });
        final Button button2 = (Button) findViewById(R.id.button2);
        button2.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                // Perform action on click

                Log.d("derek", "call coredump()");

                TextView tv = (TextView) findViewById(R.id.sample_text);
                tv.setText(coreDump());


            }
        });

        Log.d("derek", "call sighandlerRegister()");
        tv.setText(sighandlerRegister());

        final Button button5 = (Button) findViewById(R.id.button5);
        button5.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                // Perform action on click

                Log.d("derek", "call socket test()");

                TextView tv = (TextView) findViewById(R.id.sample_text);
                tv.setText(sockettest());


            }
        });


        final Button button3 = (Button) findViewById(R.id.button3);
        button3.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                // Perform action on click

                Log.d("derek", "call threadtest()");

                TextView tv = (TextView) findViewById(R.id.sample_text);
                tv.setText(threadtest());


            }
        });


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String coreDump();
    public native String fork();
    public native String sighandlerRegister();
    public native String sockettest();
    public native String threadtest();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }



}
