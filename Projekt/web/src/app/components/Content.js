"use client"
import axios from 'axios'
import styles from "../page.module.css"
import { useState, useEffect } from 'react'

export default function Content() {
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
        <h1>Welcome to our NLP Platform</h1>
        <p>Here you can access many simple models that provide somewhat good quality content analysis and translation.</p>
        <p>Our project also has an API interface, get an API key by creating an account!</p>
        <p>Currently available features: Sentiment Analysis and Machine Translation</p>
      </div>
      <div>
        <button onClick={updateStatus}>Ping!</button>
        <span>{ status }</span>
      </div>
    </div>
  );
}
