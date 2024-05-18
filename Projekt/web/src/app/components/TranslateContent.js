"use client"
import axios from 'axios'
import styles from "../page.module.css"
import { useState, useEffect } from 'react'

export default function TranslateContent() {
  const [status, setStatus] = useState("Press button for API Status")

  const pingStatus = () => {
      fetch('http://localhost:8080/api/translate', {
        method: 'POST',
        headers: {
          'Accept': 'application/json',
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
          srcLanguage: "en",
          dstLanguage: "pl",
          data: "Hello World"
        })
      })
      .then((res) => res.json())
      .then((data) => {
        setStatus(data.data)
      })
  }

  const updateStatus = () => {
    setStatus("Loading...")
    pingStatus()
  }

  return (
    <div className={styles.content}>
      <div className={styles.mainpadding}>
        <h1>Machine Translation Tool!</h1>
        <p>Translate text from one language to other!</p>
        <p>Select a model from a list and choose a langauge pair</p>
        <textarea cols="50" rows="20" maxLength="1024"></textarea>
        <span>-&gt;</span>
        <textarea cols="50" rows="20" maxLength="1024" value={status} disabled></textarea>
        <button onClick={updateStatus}>Translate!</button>
      </div>
    </div>
  );
}

