package com.example.druggist.rpncalculator

import android.app.Activity
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_preferences.*
import android.text.Editable
import android.text.TextWatcher







class PreferencesActivity : AppCompatActivity() {
    var darkTheme = false
    var precision = -1
    override fun onCreate(savedInstanceState: Bundle?) {

        val extras = intent.extras

        darkTheme = extras.getBoolean("DarkTheme", false)
        precision = extras.getInt("Precision", -1)

        if (savedInstanceState != null) {
            with(savedInstanceState) {
                precision = getInt("Precision")
                darkTheme = getBoolean("DarkTheme")
            }
        }

        setTheme(if(darkTheme) android.R.style.ThemeOverlay_Material_Dark else android.R.style.ThemeOverlay_Material_Light)
        setContentView(R.layout.activity_preferences)

        darkThemeBtn.isChecked = darkTheme
        precisionBox.setText(precision.toString())

        super.onCreate(savedInstanceState)

        darkThemeBtn.setOnCheckedChangeListener { _, isChecked ->
            darkTheme = isChecked
            recreate()
        }
        precisionBox.addTextChangedListener(object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {}

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {}

            override fun afterTextChanged(s: Editable) {
                precision = precisionBox.text.toString().toInt()
            }
        })
    }

    override fun onSaveInstanceState(outState: Bundle?) {
        outState?.run {
            putInt("Precision", precision)
            putBoolean("DarkTheme", darkTheme)
        }
        super.onSaveInstanceState(outState)
    }

    override fun finish() {
        val data = Intent()
        data.putExtra("DarkTheme", darkTheme)
        data.putExtra("Precision", precision)
        setResult(Activity.RESULT_OK, data)
        super.finish()
    }

}
