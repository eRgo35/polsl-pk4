'use client'
import * as React from 'react';
import { Button, Grid, InputAdornment, LinearProgress, Paper, TextField, Typography } from "@mui/material";
import { baseUrl } from '../lib/backend';
import SaveIcon from '@mui/icons-material/Save';
import Language from '@mui/icons-material/Language';

export default function DetectForm() {
  const [inputText, setInputText] = React.useState("");
  const [analysis, setAnalysis] = React.useState(null);
  const [isLoading, setIsLoading] = React.useState(false);

  const languages = {
    "af": ["Afrikaans", "🇿🇦"],
    "sq": ["Albanian", "🇦🇱"],
    "am": ["Amharic", "🇪🇹"],
    "ar": ["Arabic", "🇦🇪"],
    "hy": ["Armenian", "🇦🇲"],
    "az": ["Azerbaijani", "🇦🇿"],
    "eu": ["Basque", "🇪🇦"],
    "be": ["Belarusian", "🇧🇾"],
    "bn": ["Bengali", "🇧🇩"],
    "bs": ["Bosnian", "🇧🇦"],
    "bg": ["Bulgarian", "🇧🇬"],
    "ca": ["Catalan", "🇦🇨"],
    "ceb": ["Cebuano", "🇵🇭"],
    "ny": ["Chichewa", "🇿🇼"],
    "zh-cn": ["Chinese (Simplified)", "🇨🇳"],
    "zh-tw": ["Chinese (Traditional)", "🇹🇼"],
    "co": ["Corsican", "🇫🇷"],
    "hr": ["Croatian", "🇭🇷"],
    "cs": ["Czech", "🇨🇿"],
    "da": ["Danish", "🇩🇰"],
    "nl": ["Dutch", "🇳🇱"],
    "en": ["English", "🇬🇧"],
    "eo": ["Esperanto", "🇪🇪"],
    "et": ["Estonian", "🇪🇪"],
    "tl": ["Filipino", "🇵🇭"],
    "fi": ["Finnish", "🇫🇮"],
    "fr": ["French", "🇫🇷"],
    "fy": ["Frisian", "🇳🇱"],
    "gl": ["Galician", "🇪🇺"],
    "ka": ["Georgian", "🇬🇪"],
    "de": ["German", "🇩🇪"],
    "el": ["Greek", "🇬🇷"],
    "gu": ["Gujarati", "🇮🇳"],
    "ht": ["Haitian Creole", "🇭🇹"],
    "ha": ["Hausa", "🇳🇬"],
    "haw": ["Hawaiian", "🇺🇸"],
    "iw": ["Hebrew", "🇮🇱"],
    "hi": ["Hindi", "🇮🇳"],
    "hmn": ["Hmong", "🇲🇰"],
    "hu": ["Hungarian", "🇭🇺"],
    "is": ["Icelandic", "🇮🇸"],
    "ig": ["Igbo", "🇳🇬"],
    "id": ["Indonesian", "🇮🇩"],
    "ga": ["Irish", "🇮🇪"],
    "it": ["Italian", "🇮🇹"],
    "ja": ["Japanese", "🇯🇵"],
    "jw": ["Javanese", "🇮🇩"],
    "kn": ["Kannada", "🇮🇳"],
    "kk": ["Kazakh", "🇰🇿"],
    "km": ["Khmer", "🇰🇭"],
    "ko": ["Korean", "🇰🇷"],
    "ku": ["Kurdish", "🇹🇯"],
    "ky": ["Kyrgyz", "🇰🇬"],
    "lo": ["Lao", "🇱🇦"],
    "la": ["Latin", "🇻🇦"],
    "lv": ["Latvian", "🇱🇻"],
    "lt": ["Lithuanian", "🇱🇹"],
    "lb": ["Luxembourgish", "🇱🇺"],
    "mk": ["Macedonian", "🇲🇰"],
    "mg": ["Malagasy", "🇲🇬"],
    "ms": ["Malay", "🇲🇾"],
    "ml": ["Malayalam", "🇮🇳"],
    "mt": ["Maltese", "🇲🇹"],
    "mi": ["Maori", "🇳🇿"],
    "mr": ["Marathi", "🇮🇳"],
    "mn": ["Mongolian", "🇲🇳"],
    "my": ["Burmese", "🇲🇲"],
    "ne": ["Nepali", "🇳🇵"],
    "no": ["Norwegian", "🇳🇴"],
    "ps": ["Pashto", "🇵🇰"],
    "fa": ["Persian", "🇮🇷"],
    "pl": ["Polish", "🇵🇱"],
    "pt": ["Portuguese", "🇵🇹"],
    "pa": ["Punjabi", "🇵🇰"],
    "ro": ["Romanian", "🇷🇴"],
    "ru": ["Russian", "🇷🇺"],
    "sm": ["Samoan", "🇼🇸"],
    "gd": ["Scottish Gaelic", "🇬🇧"],
    "sr": ["Serbian", "🇷🇸"],
    "st": ["Sesotho", "🇿🇦"],
    "sn": ["Shona", "🇿🇿"],
    "sd": ["Sindhi", "🇵🇰"],
    "si": ["Sinhala", "🇱🇰"],
    "sk": ["Slovak", "🇸🇰"],
    "sl": ["Slovenian", "🇸🇮"],
    "so": ["Somali", "🇸🇴"],
    "es": ["Spanish", "🇪🇸"],
    "su": ["Sundanese", "🇮🇩"],
    "sw": ["Swahili", "🇰🇪"],
    "sv": ["Swedish", "🇸🇪"],
    "tg": ["Tajik", "🇹🇯"],
    "ta": ["Tamil", "🇮🇳"],
    "te": ["Telugu", "🇮🇳"],
    "th": ["Thai", "🇹🇭"],
    "tr": ["Turkish", "🇹🇷"],
    "uk": ["Ukrainian", "🇺🇦"],
    "ur": ["Urdu", "🇵🇰"],
    "uz": ["Uzbek", "🇺🇿"],
    "vi": ["Vietnamese", "🇻🇳"],
    "cy": ["Welsh", "🇬🇧"],
    "xh": ["Xhosa", "🇿🇦"],
  };

  const handleAnalyze = async () => {
    setIsLoading(true);

    try {
      await fetch(`${baseUrl}/api/detect`, {
        method: 'POST',
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json',
          'Authorization': '17e1c9878d714c7f83209cc4084ea632'
        },
        body: JSON.stringify({
          data: inputText
        })
      })
        .then(res => res.json())
        .then(({ data }) => {
          console.log(data)
          setAnalysis(data)
        })
    } catch (err) {
      console.error(err);
      setAnalysis("An error occoured!");
    }

    setIsLoading(false);
  };

  const handleExport = () => {
    const data = "data:text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(analysis))
    const date = new Date()
    const exportTitle = `analysis-${date.getFullYear()}-${date.getMonth() + 1}-${date.getDate()}-${date.getHours()}-${date.getMinutes()}-${date.getSeconds()}.json`
    const download = document.createElement('a');
    download.setAttribute("href", data);
    download.setAttribute("download", exportTitle);
    document.body.appendChild(download);
    download.click()
    download.remove()
  }

  return (
    <Paper sx={{ padding: 3 }}>
      <h1>Language Detection Tool</h1>

      <p>Analyzes text content and decides what language it is.</p>
      <Grid container spacing={2}>
        <Grid item xs={12}>
          <TextField
            label="Enter Text for Analysis"
            multiline
            minRows={4}
            fullWidth
            value={inputText}
            onChange={e => setInputText(e.target.value)}
            InputProps={{
              endAdornment: (
                <InputAdornment position="end">
                  <Button variant="contained" size="small" endIcon={<Language />} onClick={handleAnalyze}>
                    Detect
                  </Button>
                </InputAdornment>
              ),
            }}
          />
          {(analysis !== null) && (
            <Grid container justifyContent="center" sx={{ mt: 4 }}>
              <Grid item xs={12} md={8}>
                <Paper variant="outlined" sx={{ padding: 2 }}>
                  <Typography variant="h5" align="center" gutterBottom>
                    Language: {languages[analysis] ? languages[analysis][0] : analysis}
                  </Typography>
                  <Typography variant="h1" align="center" gutterBottom>
                    {languages[analysis] ? languages[analysis][1] : ""}
                  </Typography>
                  <Grid container justifyContent="center">
                    <Grid item>
                      <Button variant="outlined" onClick={handleExport} startIcon={<SaveIcon />}>
                        Export to JSON
                      </Button>
                    </Grid>
                  </Grid>
                </Paper>
              </Grid>
            </Grid>
          )}
          {isLoading ? <LinearProgress sx={{ mt: 2 }} /> : ""}
        </Grid>
      </Grid>
    </Paper>
  );
}