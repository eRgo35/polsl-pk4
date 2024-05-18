"use client"
import axios from 'axios'
import styles from "../page.module.css"
import { useState, useEffect } from 'react'

export default function SentimentContent() {
  const [status, setStatus] = useState("I love Natural Language Processing!")
  const [sentiment, setSentiment] = useState("Response placeholder")

  const pingStatus = () => {
    fetch('http://c2yz.com:8080/api/sentiment', {
      method: 'POST',
      headers: {
        'Accept': 'application/json',
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({
        mode: "non",
        data: status
      })
    })
    .then((res) => res.json())
    .then((data) => {
      console.log(data)
      setSentiment(JSON.stringify(data[0]))
    })
  }

  const updateStatus = () => {
    setSentiment("Loading...")
    pingStatus()
  }
  
  return (
    <div className={styles.content}>
      <div className={styles.mainpadding}>
        <h1>Sentiment Analysis Tool</h1>

        <p>Analyzes text content and decided whether the text is positive or negative.</p>
        <p>Choose which model you prefer.</p>
        <p>Besides positive/negative answer, website also displays confidence level</p>
        <textarea className={styles.boxes} name="text" rows="10" cols="100" maxLength="2048" value={status} onChange={e => setStatus(e.target.value)}></textarea>
        <button onClick={updateStatus}>Analyze!</button>
        <h1>{sentiment}</h1>
      </div>
    </div>
  );
}

