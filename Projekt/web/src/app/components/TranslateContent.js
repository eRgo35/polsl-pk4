"use client"
import axios from 'axios'
import styles from "../page.module.css"
import { useState, useEffect } from 'react'

export default function TranslateContent() {
  const [status, setStatus] = useState("Przetwarzanie języka naturalnego")
  const [translated, setTranslated] = useState("Response placeholder")

  const pingStatus = () => {
      fetch('http://c2yz.com:8080/api/translate', {
        method: 'POST',
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
          srcLanguage: "en",
          dstLanguage: "pl",
          data: status
        })
      })
      .then((res) => res.json())
      .then((data) => {
        console.log(data)
        setTranslated(data[0].translation_text)
      })
  }

  const updateStatus = () => {
    setTranslated("Loading...")
    pingStatus()
  }

  return (
    <div className={styles.content}>
      <div className={styles.mainpadding}>
        <h1>Machine Translation Tool!</h1>
        <p>Translate text from one language to other!</p>
        <p>Select a model from a list and choose a langauge pair</p>
        <textarea className={styles.boxes} cols="50" rows="10" maxLength="1024" value={status} onChange={e => setStatus(e.target.value)}></textarea>
        <span>-&gt;</span>
        <textarea className={styles.boxes} cols="50" rows="10" maxLength="1024" value={translated} disabled></textarea>
        <button onClick={updateStatus}>Translate!</button>
        <h1>Current: pl -&gt; en</h1>
      </div>
    </div>
  );
}

