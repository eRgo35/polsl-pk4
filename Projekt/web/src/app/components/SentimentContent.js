"use client"
import axios from 'axios'
import styles from "../page.module.css"
import { useState, useEffect } from 'react'

export default function SentimentContent() {
  const [status, setStatus] = useState("Press button for API Status")

  const pingStatus = () => {
      fetch('http://localhost:8080/api/ping')
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
        <h1>Sentiment Analysis Tool</h1>

        <p>Analyzes text content and decided whether the text is positive or negative.</p>
        <p>Choose which model you prefer.</p>
        <p>Besides positive/negative answer, website also displays confidence level</p>
        <textarea name="text" rows="20" cols="100" maxLength="2048" value={status}></textarea>
        <button onClick={updateStatus}>Analyze!</button>
      </div>
    </div>
  );
}

